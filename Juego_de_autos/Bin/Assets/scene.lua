
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
        playonStart = "Assets/Sounds/mainTheme.mp3",
        loopStart = "17105",
        loopEnd = "214244",
        soundDimension = "2D",
        vol = "0.2"
    },
    RaceManager = {
        checkpoint0 =  "2 1 -8",
        checkpoint1 =  "2 1 -27",
        checkpoint2 =  "2 1 -44",
        checkpoint3 =  "2 4 -75",
        checkpoint4 =  "-0.7f 9 -68",
        checkpoint5 =  "-8.7f 16 -78",
        checkpoint6 =  "-21.75f 16,-75",
        checkpoint7 =  "-34.75f 13,-71",
        checkpoint8 =  "-40 10,-63",
        checkpoint9 =  "-41.75f 4,-53",
        checkpoint10 =  "-42 1,-43",
        checkpoint11 =  "-42.5f -0.3f,-34",
        checkpoint12 =  "-42.5f -0.3f -24",
        checkpoint13 =  "-42.5f -0.3f -12.5f",
        checkpoint14 =  "-42.5f -0.3f 0",
        checkpoint15 =  "-42.5f -0.3f 11.2f",
        checkpoint16 =  "-42.5f -0.3f 23",
        checkpoint17 =  "-42.5f 1.7f 36.5f",
        checkpoint18 =  "-43.3f 4.2f 47",
        checkpoint19 =  "-50 6.8f 55.7f",
        checkpoint20 =  "-60 8 57",
        checkpoint21 =  "-69.8f 8.8f 53.6f",
        checkpoint22 =  "-76 10 45",
        checkpoint23 =  "-77 10.8f 34.7f",
        checkpoint24 =  "-72.5f 11.7f 25",
        checkpoint25 =  "-63.5f 12 20.3f",
        checkpoint26 =  "-52.5f 12.2f 18",
        checkpoint27 =  "-41.3f 12.25f 17",
        checkpoint28 =  "-30.5f 12.25f 17",
        checkpoint29 =  "-18.6f 12.25f 17",
        checkpoint30 =  "-3.5f 12.25f 17",
        checkpoint31 =  "-7.3f 13.5f 17",
        checkpoint32 =  "21.21f 10.1f 17",
        checkpoint33 =  "46 10.5f 15.2f",
        checkpoint34 =  "60 11 -6.8f",
        checkpoint35 =  "66.5f 10.8f -1.8f",
        checkpoint36 =  "77.7f 9.41f -9.5f",
        checkpoint37 =  "90 8.3f -11.8f",
        checkpoint38 =  "105 7.6f -12.6f",
        checkpoint39 =  "127 7.6f -12.6f",
        checkpoint40 =  "147 4.7f -12.6f",
        checkpoint41 =  "161 0.7f -12.6f",
        checkpoint42 =  "180 0.7f -12.6f",
        checkpoint43 =  "200 0.7f -12.6f",
        checkpoint44 =  "224 1.4f -12.6f",
        checkpoint45 =  "236 7 -12.6f",
        checkpoint46 =  "255.6f 13.5f -12.6f",
        checkpoint47 =  "269 16.9f -12.6f",
        checkpoint48 =  "286 18.64f -12.6f",
        checkpoint49 =  "300 15.91f -12",
        checkpoint50 =  "313 9.6f -9.8f",
        checkpoint51 =  "323 1.25f -3.59f",
        checkpoint52 =  "329.7f -5 2.9f",
        checkpoint53 =  "333 -10 9.7f",
        checkpoint54 =  "338 16.3f 20.7f",
        checkpoint55 =  "340 20 30.3f",
        checkpoint56 =  "341 -23 41.4f",
        checkpoint57 =  "341 -24.5f 50",
        checkpoint58 =  "341 -25 61",
        checkpoint59 =  "341 -23.7f 71",
        checkpoint60 =  "341.3f -20 85",
        checkpoint61 =  "338 -16.5f 97",
        checkpoint62 =  "335 -12.5f 106.75f",
        checkpoint62 =  "328.5f -7.5f 118.45f",
        checkpoint63 =  "319 -2 128.5f",
        checkpoint64 =  "",
        checkpoint65 =  "",
        checkpoint66 =  "",
        checkpoint67 =  "",
        checkpoint68 =  "",
        checkpoint69 =  ""
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
            posx =  "0.45",
            posy =  ".05",
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
            posx =  "0.45",
            posy =  ".05",
            align = "left",
            sizex = "0.08",
            sizey = "0.08",
            topcolor = "1 1 1",
            bottomcolor = "1 1 1",
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
            thrust = 5000,
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
            thrust = 5000,
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
            mass = 1,
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
        },
        RigidBodyComponent = {
            mass = 1,
            friction = "0.0"
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
EnemyCar = {
    Transform = {
        position = "0 15 0",
        rotation = "0 0 0",
        scale = "10 10 10"
    },
    MeshRenderer = {
        file =  "EnemyCar.mesh"
    },
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/engine.wav"
    },
    EnemyAI = {
        enemySpeed = "5",
        StartSeparation = "5"
    },
}

entities = { "coche", "mainCam", "raceManager",
            "lapsText", "positionText", "countdownText", "velocityText", "timerText", "laptimerText",
            "Area01_RoadMain", "Area01_RoadBorder", "Area01_Vegetation", "Area01_Extra", "Area01_Terrain", "Area01_Boosts",
            "Area02_RoadMain", "Area02_RoadBorder", "Area02_Extra", "Area02_Boosts",
            "Area03_RoadMain", "Area03_RoadBorder", "Area03_Vegetation", "Area03_Extra", "Area03_Terrain",
            "Area04_Vegetation", "Area04_Extra", "Area04_Terrain", "Area05_Extra",
            "Area01_RoadWalls", "Area02_RoadWalls", "Area03_RoadWalls",
            "Main_Terrain", "Main_Water", "SkyboxMesh",
            "EnemyCar"
        }