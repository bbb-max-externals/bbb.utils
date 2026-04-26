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
        "gridsnaponopen": 0,
        "objectsnaponopen": 1,
        "statusbarvisible": 2,
        "toolbarvisible": 2,
        "lefttoolbarpinned": 0,
        "toptoolbarpinned": 0,
        "righttoolbarpinned": 0,
        "bottomtoolbarpinned": 0,
        "tallnewobj": 0,
        "boxanimatetime": 200,
        "enablehscroll": 1,
        "enablevscroll": 1,
        "description": "",
        "digest": "",
        "tags": "",
        "style": "",
        "boxes": [
            {
                "box": {
                    "id": "obj-1",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        50.0,
                        30.0,
                        600.0,
                        28.0
                    ],
                    "text": "bbb.utils.env",
                    "fontsize": 18,
                    "fontface": 1
                }
            },
            {
                "box": {
                    "id": "obj-2",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        50.0,
                        65.0,
                        600.0,
                        20.0
                    ],
                    "text": "Read and write environment variables"
                }
            },
            {
                "box": {
                    "id": "obj-3",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        50.0,
                        105.0,
                        150.0,
                        20.0
                    ],
                    "text": "--- Messages ---"
                }
            },
            {
                "box": {
                    "id": "obj-4",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        50.0,
                        127.0,
                        500.0,
                        20.0
                    ],
                    "text": "get <name> \u2014 read environment variable"
                }
            },
            {
                "box": {
                    "id": "obj-5",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        50.0,
                        147.0,
                        500.0,
                        20.0
                    ],
                    "text": "set <name> <value> \u2014 set environment variable"
                }
            },
            {
                "box": {
                    "id": "obj-6",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        50.0,
                        167.0,
                        500.0,
                        20.0
                    ],
                    "text": "unset <name> \u2014 unset environment variable"
                }
            },
            {
                "box": {
                    "id": "obj-7",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        50.0,
                        202.0,
                        150.0,
                        20.0
                    ],
                    "text": "--- Example ---"
                }
            },
            {
                "box": {
                    "id": "obj-8",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "patching_rect": [
                        300.0,
                        232.0,
                        150.0,
                        22.0
                    ],
                    "text": "bbb.utils.env",
                    "outlettype": [
                        ""
                    ]
                }
            },
            {
                "box": {
                    "id": "obj-9",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "patching_rect": [
                        300.0,
                        267.0,
                        200.0,
                        22.0
                    ],
                    "text": "get HOME",
                    "outlettype": [
                        ""
                    ]
                }
            },
            {
                "box": {
                    "id": "obj-10",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "patching_rect": [
                        300.0,
                        297.0,
                        200.0,
                        22.0
                    ],
                    "text": "set MY_VAR hello",
                    "outlettype": [
                        ""
                    ]
                }
            },
            {
                "box": {
                    "id": "obj-11",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        300.0,
                        357.0,
                        50.0,
                        22.0
                    ],
                    "text": "print"
                }
            },
            {
                "box": {
                    "id": "obj-12",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        50.0,
                        407.0,
                        150.0,
                        20.0
                    ],
                    "text": "--- Inlets ---"
                }
            },
            {
                "box": {
                    "id": "obj-13",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        50.0,
                        429.0,
                        500.0,
                        20.0
                    ],
                    "text": "inlet 0: get, set, unset messages"
                }
            },
            {
                "box": {
                    "id": "obj-14",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        50.0,
                        464.0,
                        150.0,
                        20.0
                    ],
                    "text": "--- Outlets ---"
                }
            },
            {
                "box": {
                    "id": "obj-15",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        50.0,
                        486.0,
                        500.0,
                        20.0
                    ],
                    "text": "outlet 0 (symbol): variable value"
                }
            }
        ],
        "lines": [
            {
                "patchline": {
                    "source": [
                        "obj-9",
                        0
                    ],
                    "destination": [
                        "obj-8",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "obj-10",
                        0
                    ],
                    "destination": [
                        "obj-8",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "obj-8",
                        0
                    ],
                    "destination": [
                        "obj-11",
                        0
                    ]
                }
            }
        ]
    }
}