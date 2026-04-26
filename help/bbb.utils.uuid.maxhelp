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
                    "text": "bbb.utils.uuid",
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
                    "text": "Generate UUID v4 strings"
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
                    "text": "bang \u2014 generate and output a UUID v4"
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
                    "text": "generate \u2014 same as bang"
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
                        182.0,
                        150.0,
                        20.0
                    ],
                    "text": "--- Example ---"
                }
            },
            {
                "box": {
                    "id": "obj-7",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 1,
                    "patching_rect": [
                        300.0,
                        212.0,
                        150.0,
                        22.0
                    ],
                    "text": "bbb.utils.uuid",
                    "outlettype": [
                        ""
                    ]
                }
            },
            {
                "box": {
                    "id": "obj-8",
                    "maxclass": "message",
                    "numinlets": 2,
                    "numoutlets": 1,
                    "patching_rect": [
                        300.0,
                        247.0,
                        200.0,
                        22.0
                    ],
                    "text": "bang",
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
                        277.0,
                        200.0,
                        22.0
                    ],
                    "text": "generate",
                    "outlettype": [
                        ""
                    ]
                }
            },
            {
                "box": {
                    "id": "obj-10",
                    "maxclass": "newobj",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        300.0,
                        337.0,
                        50.0,
                        22.0
                    ],
                    "text": "print"
                }
            },
            {
                "box": {
                    "id": "obj-11",
                    "maxclass": "comment",
                    "numinlets": 1,
                    "numoutlets": 0,
                    "patching_rect": [
                        50.0,
                        387.0,
                        150.0,
                        20.0
                    ],
                    "text": "--- Inlets ---"
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
                        409.0,
                        500.0,
                        20.0
                    ],
                    "text": "inlet 0: bang (generate UUID)"
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
                        444.0,
                        150.0,
                        20.0
                    ],
                    "text": "--- Outlets ---"
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
                        466.0,
                        500.0,
                        20.0
                    ],
                    "text": "outlet 0 (symbol): UUID string (8-4-4-4-12 format)"
                }
            }
        ],
        "lines": [
            {
                "patchline": {
                    "source": [
                        "obj-8",
                        0
                    ],
                    "destination": [
                        "obj-7",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "obj-9",
                        0
                    ],
                    "destination": [
                        "obj-7",
                        0
                    ]
                }
            },
            {
                "patchline": {
                    "source": [
                        "obj-7",
                        0
                    ],
                    "destination": [
                        "obj-10",
                        0
                    ]
                }
            }
        ]
    }
}