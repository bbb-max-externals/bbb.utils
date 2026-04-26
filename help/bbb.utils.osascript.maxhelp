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
                    "text": "bbb.utils.osascript",
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
                    "text": "Execute AppleScript / JavaScript for Automation (JXA) from Max.\nUses macOS osascript command internally.",
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
                        260,
                        22.0
                    ],
                    "text": "exec display dialog \\\"Hello\\\""
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
                        295,
                        135,
                        400,
                        20.0
                    ],
                    "text": "Execute inline AppleScript source"
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
                        280,
                        22.0
                    ],
                    "text": "exec Application(\\\"Finder\\\")"
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
                        315,
                        168,
                        400,
                        20.0
                    ],
                    "text": "Execute inline JavaScript (set @language javascript)"
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
                        150,
                        22.0
                    ],
                    "text": "run script.scpt"
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
                        185,
                        201,
                        400,
                        20.0
                    ],
                    "text": "Run a script file"
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
                    "attr": "language",
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
                        400,
                        20.0
                    ],
                    "text": "Script language: applescript (0) / javascript (1)"
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
                        400,
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
                    "text": "0 (left):  script result (symbol)"
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
                    "text": "2 (right): done / error <msg>"
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
                        200,
                        22.0
                    ],
                    "text": "bbb.utils.osascript",
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
                        170,
                        22.0
                    ],
                    "text": "print osascript.result"
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
                        210,
                        530,
                        170,
                        22.0
                    ],
                    "text": "print osascript.stderr"
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
                        400,
                        530,
                        170,
                        22.0
                    ],
                    "text": "print osascript.status"
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