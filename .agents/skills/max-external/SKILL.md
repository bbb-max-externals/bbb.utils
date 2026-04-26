---
name: max-external
description: Max/MSPのエクスターナルオブジェクトをmin-api + CMakeで作成する
---

# max-external

## 前提

- macOS
- CMake 3.19+
- Xcode CLI tools
- min-api / max-sdk-base は git submodule として `deps/min-api/` に配置済みであること

## プロジェクト構造

```
project/
├── CMakeLists.txt              # ルートCMake
├── deps/
│   └── min-api/                # git submodule (max-sdk-base を含む)
├── source/
│   ├── projects/
│   │   └── bbb.xxx/            # external ごとのディレクトリ
│   │       ├── CMakeLists.txt
│   │       ├── bbb.xxx.cpp
│   │       └── bbb.xxx.maxhelp
│   └── bbb/                    # 共有ヘッダ (任意)
├── externals/                  # ビルド成果物 (.mxo)
├── help/                       # helpファイルのコピー
├── scripts/
│   └── generate_help.py        # maxhelp 生成スクリプト (推奨)
└── package-info.json           # Max package metadata
```

## 新規 external の追加手順

### 1. ソースファイル作成

`source/projects/bbb.xxx/bbb.xxx.cpp`:

```cpp
#include "c74_min.h"

class my_object : public c74::min::object<my_object> {
public:
    MIN_DESCRIPTION{"Description of this object."};
    MIN_TAGS{"tag1, tag2"};
    MIN_AUTHOR{"author"};

    c74::min::inlet<> input{this, "(anything) input"};
    c74::min::outlet<> output{this, "(anything) output"};

    // bang message
    c74::min::message<> bang_msg{this, "bang", "respond to bang",
        MIN_FUNCTION {
            output.send(c74::min::k_sym_bang);
            return {};
        }
    };
};

MIN_EXTERNAL(my_object);
```

### 2. プロジェクト CMakeLists.txt

`source/projects/bbb.xxx/CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.19)

# min-api のパスを解決
if(NOT DEFINED C74_MIN_API_DIR)
    set(C74_MIN_API_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/min-api")
endif()

# プロジェクト名は external 名と一致させる (.mxo の名前になる)
project(bbb.xxx)

set(SOURCE_FILES
    ${PROJECT_NAME}.cpp
)

# min-api の pre-target script
include(${C74_MIN_API_DIR}/script/min-pretarget.cmake)

# ライブラリを追加 (libartnet 等を使う場合)
# target_link_libraries(${PROJECT_NAME} PRIVATE artnet)

# help ファイルのコピー (任意)
set(HELP_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.maxhelp")
set(HELP_DEST "${CMAKE_CURRENT_SOURCE_DIR}/../../../help/${PROJECT_NAME}.maxhelp")
if(EXISTS "${HELP_SOURCE}")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${HELP_SOURCE}" "${HELP_DEST}"
    )
endif()

# min-api の post-target script
include(${C74_MIN_API_DIR}/script/min-posttarget.cmake)
```

### 3. ルート CMakeLists.txt に add_subdirectory

```cmake
add_subdirectory(source/projects/bbb.xxx)
```

### 4. ビルド

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

成果物は `externals/bbb.xxx.mxo` に出力される。

## min-api のハマリどころ

### attribute はコンストラクタ完了後に設定される

`@bind_ip`, `@mode` 等の attribute はコンストラクタ実行時にはまだデフォルト値。
初期化処理は `m_init_timer.delay(0)` で遅延させること:

```cpp
c74::min::timer<c74::min::timer_options::defer_delivery> m_init_timer{this,
    MIN_FUNCTION {
        init();   // ここで attribute が反映済み
        return {};
    }
};

my_object() {
    m_init_timer.delay(0);
}
```

### outlet への出力はメインスレッドのみ

worker thread から `output.send()` を呼んでも何も出ない。
timer callback はメインスレッドで実行されるので、定期送信には timer を使う:

```cpp
c74::min::timer<c74::min::timer_options::defer_delivery> m_timer{this,
    MIN_FUNCTION {
        // output.send() が使える
        return {};
    }
};
```

**worker thread から timer の delay() を呼んでも発火しない。**

### attribute の enum_map

int attribute を attrui でドロップダウン表示するには `enum_map` を使う:

```cpp
c74::min::attribute<int> mode{this, "mode", 0,
    c74::min::description{"Output mode."},
    c74::min::enum_map{"automatic", "bang", "update", "change", "forced"}
};
```

**`range{"a", "b"}` + `style::enum_index` は "bad number" エラーになる。`enum_map` を使うこと。**

### attribute の setter callback

attribute 変更時に副作用を入れたい場合:

```cpp
c74::min::attribute<int> mode{this, "mode", 0,
    c74::min::enum_map{"automatic", "bang", "update"},
    c74::min::setter{[this](const c74::min::atoms& args, int) -> c74::min::atoms {
        // 副作用
        return args;  // 必ず args を返す。空を返すとデフォルト値になる
    }}
};
```

### cout / cerr

min-api では `cout` / `cerr` はメンバ変数。グローバルではない:

```cpp
cout << "message" << c74::min::endl;  // OK
std::cout << "message" << std::endl;  // NG (Maxコンソールに出ない)
```

### outlet::send API

selector + atoms を送る場合、selector を atoms の先頭に symbol として入れて `send(atoms)` を使う:

```cpp
// NG: send("selector", atoms)
// OK:
c74::min::atoms a;
a.push_back(c74::min::symbol("list"));
a.push_back(42);
output.send(a);
```

### NIL マクロ衝突

Max SDK の `ext_mess.h` が `#define NIL ((void *)0)` を定義。
oscpp 等の `NIL` enum 値と衝突する場合:

```cpp
#pragma push_macro("NIL")
#undef NIL
// ... osc include ...
// pop_macro は使わない (bbb-osc 側で NIL を使わない前提)
```

## バージョン管理

git commit count から自動生成する:

```cmake
# CMakeLists.txt
add_custom_target(generate_version ALL
    COMMAND ${CMAKE_COMMAND}
        -DWORKING_DIR=${CMAKE_CURRENT_SOURCE_DIR}
        -DVERSION_FILE=${CMAKE_CURRENT_SOURCE_DIR}/source/bbb/version.h
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/generate_version.cmake
)
```

```cmake
# cmake/generate_version.cmake
execute_process(
    COMMAND git rev-list --count HEAD
    WORKING_DIRECTORY ${WORKING_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_COUNT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
if(NOT GIT_COMMIT_COUNT)
    set(GIT_COMMIT_COUNT 1)
endif()
set(VERSION_STRING "0.0.${GIT_COMMIT_COUNT}")
file(WRITE ${VERSION_FILE} "#pragma once\n#define BBB_ARTNET_VERSION \"${VERSION_STRING}\"\n")
```

## help ファイル (maxhelp)

maxhelp は JSON (旧形式)。Python スクリプト等で生成するのが推奨。
生成後 `help/` にコピーして Max から参照可能にする。

## package-info.json

Max にパッケージとして認識させるため:

```json
{
    "title": "bbb.xxx",
    "description": "Description",
    "author": "author",
    "website": "",
    "extends": "",
    "extensible": 0,
    "homepatcher": "",
    "max_version_min": "8.0",
    "os": {
        "macintosh": {
            "externals": [
                "externals/"
            ],
            "help": [
                "help/"
            ]
        }
    },
    "filelist": {
        "externals/bbb.xxx.mxo": {}
    }
}
```
