ButtonManager = {
    SceneChangeButton = {}
}

locomotorImg = {
    UIImageLM = { 
        posx = "0",
        posy = "0",
        sizex = "1",
        sizey = "1",
        img = "MenuBack"
    }
}
raceButton = {
    UIImageLM = { 
        interactive = "",
        posx = "0",
        posy = ".7",
        sizex = ".25",
        sizey = ".15",
        img = "UIPanel",
        top = "20"
    },

    UITextLM = {
        font =  "Heavitas",
        text = "RACE",
        posx =  "-.4",
        posy =  ".665",
        align = "center",
        sizex = "0.07",
        sizey = "0.07",
        topcolor = "0.1 0.1 0.1",
        bottomcolor = "0.1 0.1 0.1"
    }
}



menuBack = {
    UIImageLM = { 
        posx = ".75",
        posy = ".80",
        sizex = ".2",
        sizey = ".2",
        img = "LocomotorImg",
        top = "-1000"
    }
}

speedButton = {
    UIImageLM = { 
        interactive = "",
        posx = ".15",
        posy = ".5",
        sizex = ".2",
        sizey = ".1",
        img = "UIPanel"
    },

    UITextLM = {
        font =  "Heavitas",
        text = "100cc",
        posx =  "-.25",
        posy =  ".525",
        align = "center",
        sizex = "0.05",
        sizey = "0.05",
        topcolor = ".2 .2 1",
        bottomcolor = ".9 .9 1"
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

titleText = {
    Transform = {
        position = "0 0 0",
        rotation = "0 0 0",
        scale = "1 1 1"
    },
    UIImageLM = { 
        posx = ".40",
        posy = "-0.01",
        sizex = "0.55",
        sizey = "0.55",
        img = "G6Logo"
    }
}

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
        main = ""
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

entities = {"ButtonManager", "raceButton", "speedButton", "locomotorImg",
"titleText", "mainCam", "carGraphic"}