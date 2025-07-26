### UDataAsset

专为存储结构化数据设计的基类（UDataAsset），每个实例是独立的资产文件（.uasset），适用于配置表、全局参数或可重用数据集。

支持引用其他 UObject（如材质、网格）；

支持 批量编辑 (BulkEdit) 高效修改数据；

原生不支持继承，需通过 蓝图子类 实现层级结构；

### UPrimaryDataAsset：增强型数据资产

继承自 UDataAsset，增加资源管理功能：

主资产ID：通过 GetPrimaryAssetId() 实现唯一标识，支持用 AssetManager 动态加载/卸载；

分包支持 (Chunking)：通过 Chunk ID 将资产打包到独立文件（如DLC），需配合 PrimaryAssetLabel 使用；

```C++
// 加载 UPrimaryDataAsset
const FPrimaryAssetId AssetId("WeaponData", "Rifle_Advanced");
UAssetManager::Get().LoadPrimaryAsset(AssetId);

// 直接访问 UDataAsset
void APlayer::ApplyConfig(UHeroData* HeroConfig) {
    MaxHealth = HeroConfig->BaseStats.Health;
}
```

#### 动态创建资产

```C++
// 运行时生成数据资产
UHeroData* CreateHeroAsset(FString Name) {
    UPackage* Pkg = CreatePackage(*FString("/Game/DynamicData/" + Name));
    UHeroData* NewAsset = NewObject<UHeroData>(Pkg, *Name, RF_Public);
    NewAsset->BaseStats.Health = 150.0f; // 初始化数据
    FAssetRegistryModule::AssetCreated(NewAsset);
    return NewAsset;
}
```

#### 分包优化 (Chunking)

创建 PrimaryAssetLabel 资产

设置 Chunk ID（如 1001）

勾选 标记目录内资产(Label Assets in My Directory)

#### 异步加载

```C++
// 非阻塞加载
FStreamableManager StreamLoader;
StreamLoader.RequestAsyncLoad(
    HeroAsset.ToSoftObjectPath(),
    [this]() { 
        UE_LOG(LogTemp, Warning, TEXT("资产加载完成!"));
    }
);
```

### 对比

![]()

### 总结

✅ 简单配置 → 基础 UDataAsset

✅ 需动态加载/卸载的资源 → UPrimaryDataAsset + AssetManager

✅ 多语言/表格数据 → DataTable + FTableRowBase

✅ 跨项目共享 → 导出为 .json 配合版本控制

❌ 高频更新数据 → 避免使用（每次修改需重新打包）

实际项目案例：《堡垒之夜》使用 UPrimaryDataAsset 管理 5000+ 武器配置，通过 Chunk ID 实现按模式动态加载武器包，首包体积减少 40%。