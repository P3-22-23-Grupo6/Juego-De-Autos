mainCam = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    Camera = 
    { 
        CameraMode = 0,
        FOV = "60",
        target = "coche" ,
        main = ""
    },
    AudioListener = {}
}
coche = {
    Transform = {
        position = "0 15 0",
        rotation = "0 0 0",
        scale = "10 10 10"
    },
    MeshRenderer = {
        file =  "BlueFalcon.mesh"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav"
    },
    PlayerController = {},
    RigidBodyComponent = {
        mass = 1,
        friction = "0.0"
    },
    ParticleSystem = {
        name = "exhaust",
        file = "Racers/JetEngine2"
    }
}

Area01_Oil = {
    Transform = {
        position = "0 25 200",
        rotation = "0 0 0",
        scale = "40 40 40"
    },
    MeshRenderer = {
        file =  "Stinger.mesh",
        static = ""
    },
    RigidBodyComponent = {
        mass = 0,
        usedAsRaycast = "",
        isTrigger = ""
    },
    OilBlind = {
        slippedtime = 3,
        ogpos = "0 25 200",
        farpos = "200 25 0"
    },
    
}

oilstain = {
    UIImageLM = { 
        posx = ".0",
        posy = ".0",
        sizex = "1",
        sizey = "1",
        img = "StainClear"
    }
}

raceManager = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    UITextLM = {
        font =  "BrunoAce",
        text = "0 fps",
        posx =  "0",
        posy =  ".02",
        align = "center",
        sizex = "0.05",
        sizey = "0.05",
        topcolor = "0 0 0",
        bottomcolor = "0 0 0",
    },
    AudioSource = {
        loops= -1,
        loopStart = "17105",
        loopEnd = "214244",
        playonStart = "Assets/Sounds/mainTheme.mp3",
        soundDimension = "2D",
        vol = "1"
    },
    RaceManager = {
        checkpoint80 = "2 1 -5",
        checkpoint0 = "2 1 -10",
        checkpoint1 = "2 1 -27",
        checkpoint2 = "2 1 -44",
        checkpoint3 = "1 6 -62",
        checkpoint4 = "-10 15 -75",
        checkpoint5 = "-30 14 -71",
        checkpoint6 = "-42 6 -55",
        checkpoint7 = "-41 4 -53",
        checkpoint8 =  "-42 1 -43",
        checkpoint12 =  "-42 0 -24",
        checkpoint13 =  "-42 -0 -12",
        checkpoint14 =  "-42 -0 0",
        checkpoint15 =  "-42 -0 11",
        checkpoint16 =  "-42 -0 23",
        checkpoint17 =  "-42 1 36",
        checkpoint18 =  "-43 4 47",
        checkpoint19 =  "-50 6 55",
        checkpoint20 =  "-60 8 57",
        checkpoint21 =  "-69 8 53",
        checkpoint22 =  "-76 10 45",
        checkpoint23 =  "-77 10 34",
        checkpoint24 =  "-72 11 25",
        checkpoint25 =  "-63 12 20",
        checkpoint26 =  "-52 12 18",
        checkpoint27 =  "-41 12 17",
        checkpoint28 =  "-30 12 17",
        checkpoint29 =  "-18 12 17",
        checkpoint30 =  "-3 12 17",
        checkpoint31 =  "-7 13 17",
        checkpoint32 =  "21 10 17",
        checkpoint33 =  "46 10 15",
        checkpoint34 =  "60 11 -6",
        checkpoint35 =  "66 10 -1",
        checkpoint36 =  "77 9 -9",
        checkpoint37 =  "90 8 -11",
        checkpoint38 =  "105 7 -12",
        checkpoint39 =  "127 7 -12",
        checkpoint40 =  "147 4 -12",
        checkpoint41 =  "161 0 -12",
        checkpoint42 =  "180 0 -12",
        checkpoint43 =  "200 0 -12",
        checkpoint44 =  "224 1 -12",
        checkpoint45 =  "236 7 -12",
        checkpoint46 =  "255 13 -12",
        checkpoint47 =  "269 16 -12",
        checkpoint48 =  "286 18 -12",
        checkpoint49 =  "300 15 -12",
        checkpoint50 =  "313 9 -9",
        checkpoint51 =  "323 1 -3",
        checkpoint52 =  "329 -5 2",
        checkpoint53 =  "333 -10 9",
        checkpoint54 =  "338 -16 20",
        checkpoint55 =  "340 -20 30",
        checkpoint56 =  "341 -23 41",
        checkpoint57 =  "341 -24 50",
        checkpoint58 =  "341 -25 61",
        checkpoint59 =  "341 -23 71",
        checkpoint60 =  "341 -20 85",
        checkpoint61 =  "338 -15 97",
        checkpoint62 =  "320 -11 106",
        checkpoint63 =  "328 -7 118",
        checkpoint64 =  "319 -2 128",
        checkpoint65 =  "250 -5 145",
        checkpoint66 =  "228 7 160",
        checkpoint67 =  "222 8 178",
        checkpoint68 =  "227 8 192",
        checkpoint69 =  "237 9 200",
        checkpoint70 =  "250 10 203",
        checkpoint71 =  "278 17 186",
        checkpoint72 =  "285 18 167",
        checkpoint73 =  "289 18 139",
        checkpoint74 =  "285 17 107",
        checkpoint75 =  "273 19 89",
        checkpoint76 =  "254 17 77",
        checkpoint77 =  "232 14 75",
        checkpoint78 =  "209 10 75",
        checkpoint79 =  "183 7 76",
        checkpoint80 =  "187 5 76",
        checkpoint81 =  "129 5 72",
        checkpoint82 =  "99 8 60",
        checkpoint83 =  "58 10 51",
        checkpoint84 =  "45 12 51",
        checkpoint85 =  "29 1 51",
        checkpoint86 =  "7 1 45",
        checkpoint87 =  "2 1 27"
    }
}
do ---------------------   UI   ------------------------------
    timerText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "BrunoAce",
            text = "00:00:000",
            posx =  ".1",
            posy =  ".15",
            align = "left",
            sizex = "0.08",
            sizey = "0.08",
            topcolor = "1 1 1",
            bottomcolor = "1 1 1",
        }
    }
    laptimerText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "BrunoAce",
            text = "00:00:000",
            posx =  ".1",
            posy =  ".05",
            align = "left",
            sizex = "0.08",
            sizey = "0.08",
            topcolor = "0.49 .88 .89",
            bottomcolor = "0.49 .88 .89",
        }
    }
    lapsText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "BrunoAce",
            text = "0 / 3",
            posx =  "-0.45",
            posy =  ".9",
            align = "left",
            sizex = "0.1",
            sizey = "0.1",
            topcolor = "1 1 1",
            bottomcolor = "1 1 1",
        }
    }
    positionText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "BrunoAce",
            text = "3 rd",
            posx =  "0.45",
            posy =  ".9",
            align = "right",
            sizex = "0.1",
            sizey = "0.1",
            topcolor = "1 1 1",
            bottomcolor = "1 1 1",
        }
    }
    countdownText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "Heavitas",
            text = "GO!",
            posx =  "0",
            posy =  ".3",
            align = "center",
            sizex = "0.15",
            sizey = "0.15",
            topcolor = "1 1 1",
            bottomcolor = "1 1 1",
        }
    }
    velocityText = {
        Transform = {
            position = "0 0 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        UITextLM = {
            font =  "BrunoAce",
            text = "100 km/h",
            posx =  "-0.45",
            posy =  ".05",
            align = "left",
            sizex = "0.05",
            sizey = "0.05",
            topcolor = "1 1 1",
            bottomcolor = "1 1 1",
        }
    }
end ----------------------------------------------------------
do ---------------------   AREA01   ------------------------------
    Area01_RoadMain = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area01_RoadMain.mesh",
            static = ""
        },
        RigidBodyComponent = {
            mass = 0,
            usedAsRaycast = ""
        },
        ParticleSystem = {
            name = "confetti",
            file = "Racers/Confetti"
        },
        AudioSource = {
            loops= -1,
            playonStart = "Assets/Sounds/crowd.mp3",
            loopStart = "00200",
            loopEnd = "02700",
            soundDimension = "3D",
            vol = "0.8"
        }
    }

    Area01_RoadBorder = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area01_RoadBorder.mesh",
            static = ""
        }
        ,
    ParticleSystem = {
        name = "test2",
        file = "Racers/Sparkler"
    }
    }

    Area01_Vegetation = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area01_Vegetation.mesh",
            static = ""
        }
    }
    Area01_Terrain = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area01_Terrain.mesh",
            static = ""
        }
    }
    Area01_Extra = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area01_Extra.mesh",
            static = ""
        }
    }
    Area01_Boosts = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area01_Boosts.mesh",
            static = ""
        },
        RigidBodyComponent = {
            mass = 0,
            usedAsRaycast = "",
            isTrigger = ""
        },
        Boost = {
            thrust = 20000,
        },
        AudioSource = {
            vol = "1"
        }
    }

end -------------------------------------------------------------------
do ---------------------   AREA02   ------------------------------
    Area02_RoadMain = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area02_RoadMain.mesh",
            static = ""
        },
        RigidBodyComponent = {
            mass = 0,
            usedAsRaycast = ""
        }
    }

    Area02_RoadBorder = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area02_RoadBorder.mesh",
            static = ""
        }
    }
    Area02_Extra = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area02_Extra.mesh",
            static = ""
        }
    }
    Area02_Boosts = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area02_Boosts.mesh",
            static = ""
        },
        RigidBodyComponent = {
            mass = 0,
            usedAsRaycast = "",
            isTrigger = ""
        },
        Boost = {
            thrust = 20000,
        },
        AudioSource = {
            vol = "1"
        }
    }

end -------------------------------------------------------------------
do ---------------------   AREA03   ------------------------------
    Area03_RoadMain = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area03_RoadMain.mesh",
            static = ""
        },
        RigidBodyComponent = {
            mass = 0,
            usedAsRaycast = ""
        }
    }

    Area03_RoadBorder = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area03_RoadBorder.mesh",
            static = ""
        }
    }

    Area03_Vegetation = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area03_Vegetation.mesh",
            static = ""
        }
    }
    Area03_Terrain = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area03_Terrain.mesh",
            static = ""
        },
        RigidBodyComponent = {
            mass = 0,
            usedAsRaycast = ""
        }
    }
    Area03_Extra = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area03_Extra.mesh",
            static = ""
        }
    }

end -------------------------------------------------------------------
do ---------------------   AREA04   ------------------------------
    Area04_Vegetation = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area04_Vegetation.mesh",
            static = ""
        }
    }
    Area04_Terrain = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area04_Terrain.mesh",
            static = ""
        }
    }
    Area04_Extra = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area04_Extra.mesh",
            static = ""
        }
    }
    Area05_Extra = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area05_Extra.mesh",
            static = ""
        }
    }
end -------------------------------------------------------------------
do ---------------------   AREA04   ------------------------------
    Area01_RoadWalls = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area01_RoadWalls.mesh",
            static = "",
            invisible = ""
        },
        RigidBodyComponent = {
            mass = 0,
            friction = "0.0"
        }
    }
    Area02_RoadWalls = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area02_RoadWalls.mesh",
            static = "",
            invisible = ""
        },
        RigidBodyComponent = {
            mass = 0,
            friction = "0.0"
        }
    }
    Area03_RoadWalls = {
        Transform = {
            position = "0 -6 0",
            rotation = "0 0 0",
            scale = "1 1 1"
        },
        MeshRenderer = {
            file =  "Area03_RoadWalls.mesh",
            static = "",
            invisible = ""
        }
    }
end -------------------------------------------------------------------

Main_Terrain = {
    Transform = {
        position = "0 -6 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Main_Terrain.mesh",
        static = ""
    }
}
Main_Water = {
    Transform = {
        position = "0 -6 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "Main_Water.mesh",
        static = ""
    }
}
SkyboxMesh = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "SkyboxMesh.mesh",
        static = ""
    }
}
do ---------------------   Enemy   ------------------------------
EnemyCar01 = {
    Transform = {
        position = "0 35 0",
        rotation = "0 0 0",
        scale = "10 10 10"
    },
    MeshRenderer = {
        file =  "Stinger.mesh"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav"
    },
    EnemyAI = {
        enemySpeed = "2",
        StartSeparation = "40"
    },
    RigidBodyComponent = {
        mass = 1,
        friction = "0.0"
    }
}
EnemyCar02 = {
    Transform = {
        position = "0 35 0",
        rotation = "0 0 0",
        scale = "10 10 10"
    },
    MeshRenderer = {
        file =  "Stinger.mesh"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav"
    },
    EnemyAI = {
        enemySpeed = "2",
        StartSeparation = "10"
    },
    RigidBodyComponent = {
        mass = 1,
        friction = "0.0"
    }
}
EnemyCar03 = {
    Transform = {
        position = "0 35 0",
        rotation = "0 0 0",
        scale = "10 10 10"
    },
    MeshRenderer = {
        file =  "Colibri.mesh"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav"
    },
    EnemyAI = {
        enemySpeed = "2",
        StartSeparation = "-40"
    },
    RigidBodyComponent = {
        mass = 1,
        friction = "0.0"
    }
}
EnemyCar04 = {
    Transform = {
        position = "0 35 0",
        rotation = "0 0 0",
        scale = "10 10 10"
    },
    MeshRenderer = {
        file =  "Colibri.mesh"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav"
    },
    EnemyAI = {
        enemySpeed = "2",
        StartSeparation = "-70"
    },
    RigidBodyComponent = {
        mass = 1,
        friction = "0.0"
    }
}
end -------------------------------------------------------------------

entities = { "coche", "mainCam", "raceManager",
            "lapsText", "positionText", "countdownText", "velocityText", "timerText", "laptimerText",
            "Area01_RoadMain", "Area01_RoadBorder", "Area01_Vegetation", "Area01_Extra", "Area01_Terrain", "Area01_Boosts",
            "Area02_RoadMain", "Area02_RoadBorder", "Area02_Extra", "Area02_Boosts",
            "Area03_RoadMain", "Area03_RoadBorder", "Area03_Vegetation", "Area03_Extra", "Area03_Terrain",
            "Area04_Vegetation", "Area04_Extra", "Area04_Terrain", "Area05_Extra",
            "Area01_RoadWalls", "Area02_RoadWalls", "Area03_RoadWalls",
            "Main_Terrain", "Main_Water", "SkyboxMesh",
            "EnemyCar01", "EnemyCar02", "EnemyCar03", "EnemyCar04",
            "Area01_Oil", "oilstain"
        }