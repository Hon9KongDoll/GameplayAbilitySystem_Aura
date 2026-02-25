

```c++
class UAbilitySystemComponent
{
    // 获取当前可激活能力列表
    GetActivatableAbilities()
}
```



```c++
struct FGameplayTag
{
    /**
     * 获取与 TagName 对应的 FGameplayTag
     * @param TagName 要查找的标签名称
     * @param ErrorIfNotFound 如果为 true，当标签不存在时会触发 ensure() 警告
     * @return 返回对应的 FGameplayTag，如果没找到则返回空 Tag
     */
	static GAMEPLAYTAGS_API FGameplayTag RequestGameplayTag(const FName& TagName, bool ErrorIfNotFound=true);
    
    /**
	 * 判断当前标签是否匹配 TagToCheck（会展开父标签进行匹配）
	 * "A.1".MatchesTag("A") 返回 True
	 * "A".MatchesTag("A.1") 返回 False
	 * 如果 TagToCheck 无效（Invalid），始终返回 False
 	 * @return 如果匹配返回 True，否则 False
 	 */
    bool MatchesTag(const FGameplayTag& TagToCheck) const;
}
```



```c++
struct FGameplayEffectContext
{
    /**
     * 返回“当前这一次应用这个效果的 Instigator ASC”
     */
    virtual UAbilitySystemComponent* GetInstigatorAbilitySystemComponent() const
    
    /**
     * 返回“最初最源头的 Instigator ASC（原始施法者）”
     */
	virtual UAbilitySystemComponent* GetOriginalInstigatorAbilitySystemComponent() const
}
```



#### GameplayEffect

- **Stacking**

  - **StackingType**

    - **StackPerSource**

      ![](Picture\StackPerSource.png)

    - **StackPerTarget**

      ![](Picture\StackPerTarget.png)

  - **StackLimitCount**

    `同一个 GameplayEffect 在目标身上最多允许存在的叠加层数`

  - **StackDurationRefreshPolicy**

    `当一个已有的叠层 GameplayEffect 再次被应用时，是否刷新持续时间`

    - **RefreshOnSuccessfulApplication**

      `每次成功叠加都刷新 Duration`

    - **NeverRefresh**

      `叠层不会刷新持续时间`

    - **ExtendDuration**

      `在原有剩余时间上延长 Duration`

  - **StackPeriodResetPolicy**

    `当一个带周期效果的 GameplayEffect 被再次叠加时，是否重置它的 Tick 计时器`

    ```
    Duration = 10 秒
    Period = 2 秒（每2秒跳一次伤害）
    
    0s   2s   4s   6s   8s   10s
         ↑    ↑    ↑
       tick tick tick
    ```

    - **ResetOnSuccessfulApplication**

      `叠层成功时，周期计时器重置`

      ```
      0s   2s   3s   5s   7s   9s
           ↑    ↑    ↑
         tick  重新开始
      ```

    - **NeverReset**

      `叠层不会影响现有 tick 节奏`

      ```
      0s   2s   3s   4s   6s   8s
           ↑    ↑
         tick  tick（按原节奏）
      ```

  - **StackExpirationPolicy**

    `当一个带叠层的 GameplayEffect 的持续时间结束时，层数是怎么消失的`

    - **ClearEntireStack**

      `当激活的 GameplayEffect 过期时，整个堆叠都会被清除`

    - **RemoveSingleStackAndRefreshDuration**

      `当前的堆叠数量会减少 1，并刷新持续时间`

      `该 GameplayEffect 不会被重新应用，只是以少一层堆叠的形式继续存在`

    - **RefreshDuration**

      `刷新 GameplayEffect 的持续时间，这实际上会让该效果在持续时间上变成无限`
      `只刷新持续时间堆叠数完全不变，可以通过 OnStackCountChange 回调来手动处理堆叠减少逻辑`



#### GameplayAbility

- **Tags**

  - **AssetTags** 

    `给这个 Ability 本身打标签`

  - **CancelAbilitiesWithTag**

    `当前 Ability 被激活时，取消所有带这些标签的 Ability`

  - **BlockAbilitiesWithTag**

    `在当前 Ability 持续期间，禁止激活带这些标签的 Ability`

  - **ActivationOwnedTags**

    `Ability 激活后，给 Owner 添加的标签`

  - **ActivationRequiredTags**

    `必须拥有这些标签才能激活 Ability`

  - **ActivationBlockedTags**

    `如果 Owner 有这些标签，则 Ability 无法激活`

  - **SourceRequiredTags**

    `Source 必须拥有这些标签才可以释放`

  - **SourceBlockedTags**

    `Source 拥有这些标签时，Ability 被禁止`

  - **TargetRequiredTags**

    `目标必须拥有这些标签，Ability 才能作用`

  - **TargetBlockedTags**

    `如果目标有这些标签，则 Ability 不会生效`

- **ReplicateInputDirectly**

  `是否把玩家的输入直接从客户端复制到服务器`

- **ReplicationPolicy**

  - **ReplicateNo - DoNotReplicate**

    `Ability 实例不会复制到客户端`

  - **ReplicateYes - Replicate**

    `Ability 实例会复制到 Owner 客户端`

- **InstancingPolicy**

  - **InstancedPerActor**

    `该 Ability 创建一个单独的实例，并在每次激活时复用这个实例`

    `可以存储持久数据 / 变量需要在每次使用前手动重置`

  - **InstancedPerExecution**

    `每次激活 Ability 时都会创建一个新的实例`

    `不会在多次激活之间保存数据`

  - **NonInstanced**

    `不创建实例，仅使用类默认对象`

    `无法存储状态 / 无法绑定 Ability Task 的委托`

- **NetExecutionPolicy**

  - **LocalOnly**

    `只在本地客户端执行，服务器不会运行这个 Ability`

  - **LocalPredicted**

    `客户端先本地预测执行，然后发送到服务器，服务器再执行并校正结果`

  - **ServerOnly**

    `只在服务器执行，客户端只是发起请求`

  - **ServerInitiated**

    `由服务器先执行，然后同步到拥有该 Ability 的客户端执行`



#### 功能流程：

##### 初始化属性

- **数据表初始化属性**

  ​	**RowStructure - AttributeMetaData**

  ![](Picture\InitializeAttributesFromDataTable.png)

  ![](Picture\InitializeAttributes.png)

- **GameplayEffect初始化属性**

  ![](Picture\InitializeAttributesFromGameplayEffect_1.png)

  ​	**GameplayEffect**

  ![](Picture\DefaultPrimaryAttributesGE.png)

