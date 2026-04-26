{
    "patcher": {
        "fileversion": 1,
        "appversion": {
            "major": 8,
            "minor": 5,
            "revision": 5,
            "architecture": "x64",
            "modernui": 1
        },
        "rect": [
            100.0,
            100.0,
            860,
            600
        ],
        "bglocked": 0,
        "openinpresentation": 0,
        "default_fontsize": 12.0,
        "default_fontface": 0,
        "default_fontname": "Arial",
        "gridonopen": 1,
        "gridsize": [
            10.0,
            10.0
        ],
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
        "boxes": [
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 18,
                    "id": "obj-1",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        20,
                        20,
                        600,
                        28.0
                    ],
                    "text": "bbb.utils.shell",
                    "fontface": 1
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-2",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        20,
                        55,
                        600,
                        40.0
                    ],
                    "text": "Execute shell commands from Max.\nSupports async execution with stdout/stderr capture.",
                    "linecount": 2
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 14,
                    "id": "obj-3",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        20,
                        100,
                        200,
                        20.0
                    ],
                    "text": "Messages",
                    "fontface": 1
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-4",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        20,
                        135,
                        160,
                        22.0
                    ],
                    "text": "exec ls -la"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-5",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        195,
                        135,
                        300,
                        20.0
                    ],
                    "text": "Execute a command string: shell -c \"command\""
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-6",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        20,
                        168,
                        220,
                        22.0
                    ],
                    "text": "exec echo \"hello world\""
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-7",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        255,
                        168,
                        300,
                        20.0
                    ],
                    "text": "Arguments are joined with spaces"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-8",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        20,
                        201,
                        140,
                        22.0
                    ],
                    "text": "run script.sh"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-9",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        175,
                        201,
                        300,
                        20.0
                    ],
                    "text": "Run a shell script file: shell script.sh"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 14,
                    "id": "obj-10",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        20,
                        250,
                        200,
                        20.0
                    ],
                    "text": "Attributes",
                    "fontface": 1
                }
            },
            {
                "box": {
                    "attr": "shell",
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-11",
                    "lock": 1,
                    "maxclass": "attrui",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        20,
                        283,
                        200,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-12",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        235,
                        283,
                        300,
                        20.0
                    ],
                    "text": "Path to the shell binary (default: /bin/bash)"
                }
            },
            {
                "box": {
                    "attr": "async",
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-13",
                    "lock": 1,
                    "maxclass": "attrui",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "outlettype": [
                        ""
                    ],
                    "patching_rect": [
                        20,
                        316,
                        200,
                        22.0
                    ]
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-14",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        235,
                        316,
                        300,
                        20.0
                    ],
                    "text": "Execute asynchronously (default: on)"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 14,
                    "id": "obj-15",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        20,
                        365,
                        200,
                        20.0
                    ],
                    "text": "Outlets",
                    "fontface": 1
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-16",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        20,
                        395,
                        400,
                        20.0
                    ],
                    "text": "0 (left):  stdout (symbol)"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-17",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        20,
                        418,
                        400,
                        20.0
                    ],
                    "text": "1 (mid):   stderr (symbol)"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-18",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        20,
                        441,
                        400,
                        20.0
                    ],
                    "text": "2 (right): done <exit_code> / error <msg>"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-19",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 3,
                    "patching_rect": [
                        20,
                        490,
                        280,
                        22.0
                    ],
                    "text": "bbb.utils.shell @shell /bin/bash",
                    "outlettype": [
                        "symbol",
                        "symbol",
                        ""
                    ]
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-20",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "patching_rect": [
                        20,
                        530,
                        140,
                        22.0
                    ],
                    "text": "print shell.stdout"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-21",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "patching_rect": [
                        180,
                        530,
                        140,
                        22.0
                    ],
                    "text": "print shell.stderr"
                }
            },
            {
                "box": {
                    "fontname": "Arial",
                    "fontsize": 12.0,
                    "id": "obj-22",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "patching_rect": [
                        340,
                        530,
                        140,
                        22.0
                    ],
                    "text": "print shell.status"
                }
            }
        ],
        "lines": [
            {
                "patchline": {
                    "destination": [
                        "obj-19",
                        0
                    ],
                    "disabled": 0,
                    "hidden": 0,
                    "source": [
                        "obj-4",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-19",
                        0
                    ],
                    "disabled": 0,
                    "hidden": 0,
                    "source": [
                        "obj-6",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-19",
                        0
                    ],
                    "disabled": 0,
                    "hidden": 0,
                    "source": [
                        "obj-8",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-19",
                        0
                    ],
                    "disabled": 0,
                    "hidden": 0,
                    "source": [
                        "obj-11",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-19",
                        0
                    ],
                    "disabled": 0,
                    "hidden": 0,
                    "source": [
                        "obj-13",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-20",
                        0
                    ],
                    "disabled": 0,
                    "hidden": 0,
                    "source": [
                        "obj-19",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-21",
                        0
                    ],
                    "disabled": 0,
                    "hidden": 0,
                    "source": [
                        "obj-19",
                        1
                    ]
                }
            },
            {
                "patchline": {
                    "destination": [
                        "obj-22",
                        0
                    ],
                    "disabled": 0,
                    "hidden": 0,
                    "source": [
                        "obj-19",
                        2
                    ]
                }
            }
        ]
    }
}