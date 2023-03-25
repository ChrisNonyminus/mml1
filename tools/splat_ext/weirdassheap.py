from segtypes.common.data import CommonSegData


class PSXSegWeirdassheap(CommonSegData):
    def get_linker_section(self) -> str:
        return ".weirdassheap"
