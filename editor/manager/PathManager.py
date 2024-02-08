class PathManager:
    __ApplicationPath = None
    Sceneuuid = ""
    WorkSpaceDir = "C:\KaleidoScopeProject\KaleidoscopeEngine\Editor\work\\test.ksproj"
    @property
    def ApplicationPath()->str:
        return PathManager.__ApplicationPath
    
    @ApplicationPath.setter
    def ApplicationPath(path:str):
            print(path)
            PathManager.__ApplicationPath = path