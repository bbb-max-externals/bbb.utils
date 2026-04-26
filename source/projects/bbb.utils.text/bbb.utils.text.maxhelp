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
            701
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
                    "text": "bbb.utils.text"
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
                    "text": "String manipulation utilities \u2014 split, join, trim, replace, case, pad"
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
                    "text": "split <delimiter> <text> \u2014 split text, output as list"
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
                    "text": "join <delimiter> <atoms...> \u2014 join atoms with delimiter"
                }
            },
            {
                "box": {
                    "id": "obj-m3",
                    "patching_rect": [
                        50,
                        167,
                        600,
                        20
                    ],
                    "text": "trim <text> \u2014 trim whitespace"
                }
            },
            {
                "box": {
                    "id": "obj-m4",
                    "patching_rect": [
                        50,
                        187,
                        600,
                        20
                    ],
                    "text": "replace <from> <to> <text> \u2014 replace all occurrences"
                }
            },
            {
                "box": {
                    "id": "obj-m5",
                    "patching_rect": [
                        50,
                        207,
                        600,
                        20
                    ],
                    "text": "upper <text> \u2014 convert to uppercase"
                }
            },
            {
                "box": {
                    "id": "obj-m6",
                    "patching_rect": [
                        50,
                        227,
                        600,
                        20
                    ],
                    "text": "lower <text> \u2014 convert to lowercase"
                }
            },
            {
                "box": {
                    "id": "obj-m7",
                    "patching_rect": [
                        50,
                        247,
                        600,
                        20
                    ],
                    "text": "length <text> \u2014 output character count"
                }
            },
            {
                "box": {
                    "id": "obj-m8",
                    "patching_rect": [
                        50,
                        267,
                        600,
                        20
                    ],
                    "text": "pad <char> <length> <text> \u2014 right-pad to length"
                }
            },
            {
                "box": {
                    "id": "obj-m9",
                    "patching_rect": [
                        50,
                        497,
                        600,
                        20
                    ],
                    "text": "pad_left <char> <length> <text> \u2014 left-pad to length"
                }
            },
            {
                "box": {
                    "id": "obj-e0",
                    "patching_rect": [
                        50,
                        532,
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
                        562,
                        150,
                        22
                    ],
                    "text": "bbb.utils.text",
                    "class": "newobj"
                }
            },
            {
                "box": {
                    "id": "ex-2",
                    "patching_rect": [
                        300,
                        592,
                        200,
                        22
                    ],
                    "text": "split , hello,world,test"
                }
            },
            {
                "box": {
                    "id": "ex-3",
                    "patching_rect": [
                        300,
                        0,
                        200,
                        22
                    ],
                    "text": "join - a b c"
                }
            },
            {
                "box": {
                    "id": "ex-4",
                    "patching_rect": [
                        300,
                        0,
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
                        552,
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
                        574,
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
                        609,
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
                        631,
                        600,
                        20
                    ],
                    "text": "outlet 0 (anything): result (symbol or list for split, int for length)"
                }
            }
        ],
        "lines": [
            {
                "patchline": {
                    "destination": [
                        [
                            11,
                            "box"
                        ],
                        0
                    ],
                    "source": [
                        [
                            12,
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
                            11,
                            "box"
                        ],
                        0
                    ],
                    "source": [
                        [
                            13,
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
                            14,
                            "box"
                        ],
                        0
                    ],
                    "source": [
                        [
                            11,
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