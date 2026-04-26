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
            721
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
                    "text": "bbb.utils.http"
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
                    "text": "HTTP client using curl \u2014 GET/POST/PUT/DELETE requests"
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
                    "text": "get <url> \u2014 HTTP GET"
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
                    "text": "post <url> \u2014 HTTP POST (set body first)"
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
                    "text": "put <url> \u2014 HTTP PUT (set body first)"
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
                    "text": "delete <url> \u2014 HTTP DELETE"
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
                    "text": "body <text> \u2014 set request body for POST/PUT"
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
                    "text": "header <key> <value> \u2014 add custom header"
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
                    "text": "headers_clear \u2014 clear all custom headers"
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
                    "text": "@content_type \u2014 Content-Type header (default: application/json)"
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
                    "text": "@timeout \u2014 request timeout in seconds (default: 30)"
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
                    "text": "bbb.utils.http",
                    "class": "newobj"
                }
            },
            {
                "box": {
                    "id": "ex-2",
                    "patching_rect": [
                        300,
                        622,
                        200,
                        22
                    ],
                    "text": "body {\"key\": \"value\"}"
                }
            },
            {
                "box": {
                    "id": "ex-3",
                    "patching_rect": [
                        300,
                        622,
                        250,
                        22
                    ],
                    "text": "get https://httpbin.org/get"
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
                    "id": "ex-5",
                    "patching_rect": [
                        450,
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
                    "text": "outlet 0 (symbol): response body"
                }
            },
            {
                "box": {
                    "id": "obj-o2",
                    "patching_rect": [
                        50,
                        651,
                        600,
                        20
                    ],
                    "text": "outlet 1 (int): HTTP status code"
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
            },
            {
                "patchline": {
                    "destination": [
                        [
                            15,
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