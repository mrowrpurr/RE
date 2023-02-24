struct Item {
    //
};

struct InventoryItem {
    uint32_t ptr;
    uint32_t quantity;
};

struct Player {
    uint32_t unk00;
    uint32_t maybeMapHex;
    uint32_t unk08;
    uint32_t unk0C;
    uint32_t screenScrollY;
    uint32_t screenScrollX;
    uint32_t unk18;
    uint32_t characterDirection;
    uint32_t unk20Ptr;
    uint32_t unk24;
    uint32_t unk28;
    uint32_t inventoryCount;
    uint32_t unk30;
    uint32_t inventoryPtr;
    uint32_t unk38;
    uint32_t unk3C;
    uint32_t actionPoints;
};