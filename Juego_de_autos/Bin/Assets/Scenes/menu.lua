ButtonManager = {
    SceneChangeButton = {},
    AudioSource = {
        vol = "0.2",
        soundDimension = "2D"
    }
}

skyboxMesh = {
    MeshRenderer = {
        file = "SkyboxMesh.mesh"
    },Transform = {
        position = "0 0 0",
        rotation = "0 180 0",
        scale = "1 1 1"
    }
}

raceButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0",
        posy = ".55",
        sizex = ".45",
        sizey = ".3",
        img = "UIPanel",
        top = "20"
    },
    UITextLM = {
        font =  "Heavitas",
        text = "RACE",
        posx =  "-.45",
        posy = ".625",
        align = "left",
        sizex = "0.45",
        sizey = "0.15",
        topcolor = ".2 .2 1",
        bottomcolor = ".9 .9 1"
    }
}

menuBack = {
    UIImageLM = { 
        posx = ".75",
        posy = ".80",
        sizex = ".2",
        sizey = ".15",
        img = "LocomotorImg",
        top = "-1000"
    }
}

speedButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0.0",
        posy = "0.4",
        sizex = "0.3",
        sizey = "0.15",
        img = "UIPanel"
    },
    UITextLM = {
        font =  "Heavitas",
        text = "100cc",
        posx =  "-.45",
        posy = "0.44",
        align = "left",
        sizex = "0.3",
        sizey = "0.075",
        topcolor = ".2 .2 1",
        bottomcolor = ".9 .9 1"
    }
}
logoImg = {
    UIImageLM = { 
        interactive = "",
        posx = "0.725",
        posy = "0.8",
        sizex = "0.285",
        sizey = "0.22",
        img = "LogoImg"
    }
}
tituloImg = {
    UIImageLM = { 
        posx = "0.05",
        posy = "0.05",
        sizex = "0.4",
        sizey = "0.3",
        img = "LocomotorImg"
    }
}
aoDecal = {
    UIImageLM = { 
        posx = "0",
        posy = "0",
        sizex = "1",
        sizey = "1",
        img = "AO_Decal"
    }
}
carGraphic = {
    Transform = {
        position = "0 -10 -30",
        rotation = "0 160 0",
        scale = "10 10 10"
    },
    MeshRenderer = {
        file =  "BlueFalcon.mesh"
    },
    Rotator = {
        Speed = "0.05"
    }
}

backMesh = {
    Transform = {
        position = "0 -5 -10",
        rotation = "0 180 0",
        scale = "1 1 1"
    },
    MeshRenderer = {
        file =  "MENU.mesh"
    }
}

mainCam = {
    Transform = {
        position = "-250 -150 100",
        rotation = "15 -30 0",
        scale = "1 1 1"
    },
    Camera = 
    { 
        CameraMode = 0,
        FOV = "40",
        main = ""
    }
}
audioHolder = {
    AudioSource = {
        loops= -1,
        playonStart = "Assets/Sounds/MenuMusic.mp3",
        loopStart = "17105",
        loopEnd = "214244",
        soundDimension = "2D",
        vol = "0.2"
    },
}
-- mainCam = {
--     Transform = {
--         position = "0 0 0",
--         rotation = "0 0 0",
--         scale = "1 1 1"
--     },
--     Camera = {
--         main = ""
--     }
-- }

entities = {"ButtonManager", "raceButton", "speedButton", "skyboxMesh", "backMesh", "mainCam", "carGraphic", "logoImg", "aoDecal", "audioHolder", "tituloImg"}