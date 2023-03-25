from segtypes.common.data import CommonSegData


class PSXSegScommon(CommonSegData):
    def get_linker_section(self) -> str:
        return ".scommon"
