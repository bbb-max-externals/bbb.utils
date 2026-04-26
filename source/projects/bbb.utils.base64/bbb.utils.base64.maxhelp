{
    "patcher": {
        "fileversion": 1,
        "appversion": {
            "major": 8,
            "minor": 6,
            "revision": 4
        },
        "classnamespace": "box",
        "rect": [
            100.0,
            100.0,
            800.0,
            700.0
        ],
        "bglocked": 1,
        "openrect": [
            0.0,
            0.0,
            0.0,
            0.0
        ],
        "openinpresentation": 0,
        "default_fontsize": 12.0,
        "default_fontface": 0,
        "default_fontname": "Arial",
        "gridonopen": 2,
        "gridsize": [
            15.0,
            15.0
        ],
        "gridsnaponopen": 2,
        "objectsnaponopen": 2,
        "statusbarvisible": 2,
        "toolbarvisible": 2,
        "lefttoolbarpinned": 2,
        "toptoolbarpinned": 2,
        "righttoolbarpinned": 2,
        "bottomtoolbarpinned": 2,
        "toolbars_pinned": 2,
        "defaultnewobjposition": 2,
        "boxes": [
            {
                "box": {
                    "id": "obj-1",
                    "patching_rect": [
                        50,
                        30,
                        600,
                        28
                    ],
                    "text": "bbb.utils.base64"
                }
            },
            {
                "box": {
                    "id": "obj-2",
                    "patching_rect": [
                        50,
                        65,
                        600,
                        20
                    ],
                    "text": "Base64 encode and decode"
                }
            },
            {
                "box": {
                    "id": "obj-3",
                    "patching_rect": [
                        50,
                        105,
                        150,
                        20
                    ],
                    "text": "--- Messages ---"
                }
            },
            {
                "box": {
                    "id": "obj-m1",
                    "patching_rect": [
                        50,
                        127,
                        600,
                        20
                    ],
                    "text": "encode <text> \u2014 base64 encode"
                }
            },
            {
                "box": {
                    "id": "obj-m2",
                    "patching_rect": [
                        50,
                        147,
                        600,
                        20
                    ],
                    "text": "decode <text> \u2014 base64 decode"
                }
            },
            {
                "box": {
                    "id": "obj-e0",
                    "patching_rect": [
                        50,
                        182,
                        150,
                        20
                    ],
                    "text": "--- Example ---"
                }
            },
            {
                "box": {
                    "id": "ex-1",
                    "patching_rect": [
                        300,
                        0,
                        150,
                        22
                    ],
                    "text": "bbb.utils.base64",
                    "class": "newobj"
                }
            },
            {
                "box": {
                    "id": "ex-2",
                    "patching_rect": [
                        300,
                        297,
                        200,
                        22
                    ],
                    "text": "encode Hello Max"
                }
            },
            {
                "box": {
                    "id": "ex-3",
                    "patching_rect": [
                        300,
                        332,
                        50,
                        22
                    ],
                    "text": "print"
                }
            },
            {
                "box": {
                    "id": "obj-i0",
                    "patching_rect": [
                        50,
                        362,
                        150,
                        20
                    ],
                    "text": "--- Inlets ---"
                }
            },
            {
                "box": {
                    "id": "obj-i1",
                    "patching_rect": [
                        50,
                        434,
                        500,
                        20
                    ],
                    "text": "inlet 0: messages"
                }
            },
            {
                "box": {
                    "id": "obj-o0",
                    "patching_rect": [
                        50,
                        469,
                        150,
                        20
                    ],
                    "text": "--- Outlets ---"
                }
            },
            {
                "box": {
                    "id": "obj-o1",
                    "patching_rect": [
                        50,
                        491,
                        600,
                        20
                    ],
                    "text": "outlet 0 (symbol): encoded or decoded result"
                }
            }
        ],
        "lines": [
            {
                "patchline": {
                    "destination": [
                        [
                            7,
                            "box"
                        ],
                        0
                    ],
                    "source": [
                        [
                            8,
                            "box"
                        ],
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        [
                            9,
                            "box"
                        ],
                        0
                    ],
                    "source": [
                        [
                            7,
                            "box"
                        ],
                        0
                    ]
                }
            }
        ],
        "parameters": {}
    }
}