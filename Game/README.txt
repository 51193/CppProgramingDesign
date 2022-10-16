Resource\Images\Sprites\Tower\TowerName\TowerName_idle.png 导入炮台待机动画的sprite_sheet

Config\Sprites\Tower\TowerName\TowerName_idle.ini 导入炮台待机动画中每张sprite_sheet的尺寸和时长，格式如下
每帧时长(ms) 单张宽度 单张高度 帧数
（数字间均用空格隔开）

将上述目录最后_idle更换为_active和_card用于导入活跃和卡片状态的sprite_sheet，ini文件也同理



Config\Data\Tower\TowerName\TowerName.ini 导入炮台属性，格式如下
攻击范围 伤害 冷却 是否为AOE



Resource\Images\Sprites\Monster\MonsterName\MonsterName_up.png 导入怪物向上移动动画的sprite_sheet

Config\Sprites\Monster\MonsterName\MonsterName_up.ini 导入怪物向上移动动画中每张sprite_sheet的尺寸和时长，格式如下
每帧时长(ms) 单张宽度 单张高度 帧数
（数字间均用空格隔开）

将上述目录最后_up更换为_down, _left和_right用于导入向其他方向移动的sprite_sheet，ini文件也同理



Config\Data\Monster\MonsterName\MonsterName.ini 导入怪物属性，格式如下
血量 移动速度 碰撞箱宽度 碰撞箱高度 动画宽度 动画高度（长度单位为：地图中每格宽20单位，高15单位）