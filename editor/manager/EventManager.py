class EventManager:
    def __init__(self):
        self._events = dict()

    def register_event(self, event_name, callback):
        if event_name not in self._events:
            self._events[event_name] = []
        self._events[event_name].append(callback)

    def trigger_event(self, event_name, *args, **kwargs):
        callbacks = self._events.get(event_name, [])
        for callback in callbacks:
            callback(*args, **kwargs)

def event_handler(event_name):
    def decorator(func):
        global event_manager
        event_manager.register_event(event_name, func)
        return func
    return decorator

event_manager = EventManager()