#!/usr/bin/env python3
"""Generate .maxhelp files for bbb.utils externals."""

import json
import sys
import os


def make_comment(id, x, y, w, text, fontsize=12.0, bold=False, linecount=None):
    box = {
        "fontname": "Arial",
        "fontsize": fontsize,
        "id": f"obj-{id}",
        "maxclass": "comment",
        "numinlets": 1,
        "numoutlets": 0,
        "patching_rect": [x, y, w, 20.0],
        "text": text,
    }
    if bold:
        box["fontface"] = 1
    if linecount:
        box["linecount"] = linecount
        box["patching_rect"][3] = 20.0 * linecount
    if fontsize >= 18:
        box["patching_rect"][3] = 28.0
    return {"box": box}


def make_message(id, x, y, text, w=None):
    box = {
        "fontname": "Arial",
        "fontsize": 12.0,
        "id": f"obj-{id}",
        "maxclass": "message",
        "numinlets": 2,
        "numoutlets": 1,
        "outlettype": [""],
        "patching_rect": [x, y, w or 200.0, 22.0],
        "text": text,
    }
    return {"box": box}


def make_newobj(id, x, y, text, numinlets=1, numoutlets=1, outlettype=None, w=None):
    box = {
        "fontname": "Arial",
        "fontsize": 12.0,
        "id": f"obj-{id}",
        "maxclass": "newobj",
        "numinlets": numinlets,
        "numoutlets": numoutlets,
        "patching_rect": [x, y, w or 200.0, 22.0],
        "text": text,
    }
    if outlettype:
        box["outlettype"] = outlettype
    return {"box": box}


def make_attrui(id, x, y, attr, w=240.0):
    box = {
        "attr": attr,
        "fontname": "Arial",
        "fontsize": 12.0,
        "id": f"obj-{id}",
        "lock": 1,
        "maxclass": "attrui",
        "numinlets": 1,
        "numoutlets": 1,
        "outlettype": [""],
        "patching_rect": [x, y, w, 22.0],
    }
    return {"box": box}


def make_patchline(src_id, src_outlet, dst_id, dst_inlet):
    return {
        "patchline": {
            "destination": [f"obj-{dst_id}", dst_inlet],
            "disabled": 0,
            "hidden": 0,
            "source": [f"obj-{src_id}", src_outlet],
        }
    }


def make_patcher(boxes, lines, w=860, h=700):
    return {
        "patcher": {
            "fileversion": 1,
            "appversion": {
                "major": 8,
                "minor": 5,
                "revision": 5,
                "architecture": "x64",
                "modernui": 1,
            },
            "rect": [100.0, 100.0, w, h],
            "bglocked": 0,
            "openinpresentation": 0,
            "default_fontsize": 12.0,
            "default_fontface": 0,
            "default_fontname": "Arial",
            "gridonopen": 1,
            "gridsize": [10.0, 10.0],
            "gridsnaponopen": 1,
            "objectsnaponopen": 1,
            "statusbarvisible": 2,
            "toolbarvisible": 1,
            "tallnewobj": 0,
            "boxanimatetime": 200,
            "enablehscroll": 1,
            "enablevscroll": 1,
            "description": "",
            "digest": "",
            "tags": "",
            "style": "",
            "subpatcher_template": "",
            "boxes": boxes,
            "lines": lines,
        }
    }


def generate_shell_help():
    boxes = []
    lines = []
    cid = [1]

    def nid():
        v = cid[0]
        cid[0] += 1
        return v

    title_id = nid()
    boxes.append(make_comment(title_id, 20, 20, 600, "bbb.utils.shell", fontsize=18, bold=True))

    desc_id = nid()
    boxes.append(make_comment(desc_id, 20, 55, 600, "Execute shell commands from Max.\n"
        "Supports async execution with stdout/stderr capture.", linecount=2))

    sec_msg_id = nid()
    boxes.append(make_comment(sec_msg_id, 20, 100, 200, "Messages", fontsize=14, bold=True))

    msg_exec1_id = nid()
    boxes.append(make_message(msg_exec1_id, 20, 135, "exec ls -la", w=160))
    cmt_exec1_id = nid()
    boxes.append(make_comment(cmt_exec1_id, 195, 135, 300, 'Execute a command string: shell -c "command"'))

    msg_exec2_id = nid()
    boxes.append(make_message(msg_exec2_id, 20, 168, 'exec echo "hello world"', w=220))
    cmt_exec2_id = nid()
    boxes.append(make_comment(cmt_exec2_id, 255, 168, 300, "Arguments are joined with spaces"))

    msg_run1_id = nid()
    boxes.append(make_message(msg_run1_id, 20, 201, "run script.sh", w=140))
    cmt_run1_id = nid()
    boxes.append(make_comment(cmt_run1_id, 175, 201, 300, "Run a shell script file: shell script.sh"))

    sec_attr_id = nid()
    boxes.append(make_comment(sec_attr_id, 20, 250, 200, "Attributes", fontsize=14, bold=True))

    attr_shell_id = nid()
    boxes.append(make_attrui(attr_shell_id, 20, 283, "shell", w=200))
    cmt_shell_id = nid()
    boxes.append(make_comment(cmt_shell_id, 235, 283, 300, "Path to the shell binary (default: /bin/bash)"))

    attr_async_id = nid()
    boxes.append(make_attrui(attr_async_id, 20, 316, "async", w=200))
    cmt_async_id = nid()
    boxes.append(make_comment(cmt_async_id, 235, 316, 300, "Execute asynchronously (default: on)"))

    sec_out_id = nid()
    boxes.append(make_comment(sec_out_id, 20, 365, 200, "Outlets", fontsize=14, bold=True))

    cmt_o0_id = nid()
    boxes.append(make_comment(cmt_o0_id, 20, 395, 400, "0 (left):  stdout (symbol)"))
    cmt_o1_id = nid()
    boxes.append(make_comment(cmt_o1_id, 20, 418, 400, "1 (mid):   stderr (symbol)"))
    cmt_o2_id = nid()
    boxes.append(make_comment(cmt_o2_id, 20, 441, 400, '2 (right): done <exit_code> / error <msg>'))

    obj_id = nid()
    boxes.append(make_newobj(obj_id, 20, 490, "bbb.utils.shell @shell /bin/bash",
                             numinlets=1, numoutlets=3,
                             outlettype=["symbol", "symbol", ""], w=280))

    print_stdout_id = nid()
    boxes.append(make_newobj(print_stdout_id, 20, 530, "print shell.stdout", w=140))
    print_stderr_id = nid()
    boxes.append(make_newobj(print_stderr_id, 180, 530, "print shell.stderr", w=140))
    print_status_id = nid()
    boxes.append(make_newobj(print_status_id, 340, 530, "print shell.status", w=140))

    lines.append(make_patchline(msg_exec1_id, 0, obj_id, 0))
    lines.append(make_patchline(msg_exec2_id, 0, obj_id, 0))
    lines.append(make_patchline(msg_run1_id, 0, obj_id, 0))
    lines.append(make_patchline(attr_shell_id, 0, obj_id, 0))
    lines.append(make_patchline(attr_async_id, 0, obj_id, 0))
    lines.append(make_patchline(obj_id, 0, print_stdout_id, 0))
    lines.append(make_patchline(obj_id, 1, print_stderr_id, 0))
    lines.append(make_patchline(obj_id, 2, print_status_id, 0))

    return make_patcher(boxes, lines, h=600)


def generate_osascript_help():
    boxes = []
    lines = []
    cid = [1]

    def nid():
        v = cid[0]
        cid[0] += 1
        return v

    title_id = nid()
    boxes.append(make_comment(title_id, 20, 20, 600, "bbb.utils.osascript", fontsize=18, bold=True))

    desc_id = nid()
    boxes.append(make_comment(desc_id, 20, 55, 600,
        "Execute AppleScript / JavaScript for Automation (JXA) from Max.\n"
        "Uses macOS osascript command internally.", linecount=2))

    sec_msg_id = nid()
    boxes.append(make_comment(sec_msg_id, 20, 100, 200, "Messages", fontsize=14, bold=True))

    msg_exec1_id = nid()
    boxes.append(make_message(msg_exec1_id, 20, 135,
        'exec display dialog \\"Hello\\"', w=260))
    cmt_exec1_id = nid()
    boxes.append(make_comment(cmt_exec1_id, 295, 135, 400,
        "Execute inline AppleScript source"))

    msg_exec2_id = nid()
    boxes.append(make_message(msg_exec2_id, 20, 168,
        'exec Application(\\\"Finder\\\")', w=280))
    cmt_exec2_id = nid()
    boxes.append(make_comment(cmt_exec2_id, 315, 168, 400,
        "Execute inline JavaScript (set @language javascript)"))

    msg_run1_id = nid()
    boxes.append(make_message(msg_run1_id, 20, 201, "run script.scpt", w=150))
    cmt_run1_id = nid()
    boxes.append(make_comment(cmt_run1_id, 185, 201, 400, "Run a script file"))

    sec_attr_id = nid()
    boxes.append(make_comment(sec_attr_id, 20, 250, 200, "Attributes", fontsize=14, bold=True))

    attr_lang_id = nid()
    boxes.append(make_attrui(attr_lang_id, 20, 283, "language", w=200))
    cmt_lang_id = nid()
    boxes.append(make_comment(cmt_lang_id, 235, 283, 400,
        "Script language: applescript (0) / javascript (1)"))

    attr_async_id = nid()
    boxes.append(make_attrui(attr_async_id, 20, 316, "async", w=200))
    cmt_async_id = nid()
    boxes.append(make_comment(cmt_async_id, 235, 316, 400,
        "Execute asynchronously (default: on)"))

    sec_out_id = nid()
    boxes.append(make_comment(sec_out_id, 20, 365, 200, "Outlets", fontsize=14, bold=True))

    cmt_o0_id = nid()
    boxes.append(make_comment(cmt_o0_id, 20, 395, 400, "0 (left):  script result (symbol)"))
    cmt_o1_id = nid()
    boxes.append(make_comment(cmt_o1_id, 20, 418, 400, "1 (mid):   stderr (symbol)"))
    cmt_o2_id = nid()
    boxes.append(make_comment(cmt_o2_id, 20, 441, 400, '2 (right): done / error <msg>'))

    obj_id = nid()
    boxes.append(make_newobj(obj_id, 20, 490, "bbb.utils.osascript",
                             numinlets=1, numoutlets=3,
                             outlettype=["symbol", "symbol", ""], w=200))

    print_result_id = nid()
    boxes.append(make_newobj(print_result_id, 20, 530, "print osascript.result", w=170))
    print_stderr_id = nid()
    boxes.append(make_newobj(print_stderr_id, 210, 530, "print osascript.stderr", w=170))
    print_status_id = nid()
    boxes.append(make_newobj(print_status_id, 400, 530, "print osascript.status", w=170))

    lines.append(make_patchline(msg_exec1_id, 0, obj_id, 0))
    lines.append(make_patchline(msg_exec2_id, 0, obj_id, 0))
    lines.append(make_patchline(msg_run1_id, 0, obj_id, 0))
    lines.append(make_patchline(attr_lang_id, 0, obj_id, 0))
    lines.append(make_patchline(attr_async_id, 0, obj_id, 0))
    lines.append(make_patchline(obj_id, 0, print_result_id, 0))
    lines.append(make_patchline(obj_id, 1, print_stderr_id, 0))
    lines.append(make_patchline(obj_id, 2, print_status_id, 0))

    return make_patcher(boxes, lines, h=600)


def write_help(data, path):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as f:
        json.dump(data, f, indent=4, ensure_ascii=False)
    print(f"  wrote {path}")


if __name__ == "__main__":
    base = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    print(f"Generating help files in {base}")

    write_help(generate_shell_help(),
               os.path.join(base, "source", "projects", "bbb.utils.shell", "bbb.utils.shell.maxhelp"))
    write_help(generate_osascript_help(),
               os.path.join(base, "source", "projects", "bbb.utils.osascript", "bbb.utils.osascript.maxhelp"))
