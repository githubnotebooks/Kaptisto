import gdb


class MyGDBStructPrinter:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        return "name:{} scores:{}".format(self.val["name_"], self.val["scores_"])


class MyGDBClassPrinter:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        return "name:{} scores:{}".format(self.val["name_"], self.val["scores_"])


def my_lookup_pretty_printer(val):
    if val.type.code == gdb.TYPE_CODE_PTR:
        return None
    if "MyGDBStruct" == val.type.tag:
        return MyGDBStructPrinter(val)
    if "MyGDBClass" == val.type.tag:
        return MyGDBClassPrinter(val)
    return None


gdb.printing.register_pretty_printer(
    gdb.current_objfile(), my_lookup_pretty_printer, replace=True
)
