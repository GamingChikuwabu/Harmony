
class mGameObject:
    def __init__(self,data) -> None:
        self.data = data
    
    def get_object_name(self)->str:
        return self.data["_name"]