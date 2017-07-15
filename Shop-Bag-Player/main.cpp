/*商品-背包-玩家*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*商品结构*/
typedef struct _Prop
{
	int id;				//道具唯一的编号
	char name[20];		//道具名
	double price;			//道具单价
	int stock;			//库存量
	char desc[50];		//说明
}Prop;

/*背包结构*/
typedef struct _Bag
{
	int playerId;			//所属玩家的id
	int count;			//当前背包中道具的数量
	int max = 8;				//背包的插槽总数-可以通过充值货币扩充
	Prop props[8];		//当前背包中的道具数组
}Bag;


/*玩家结构*/
typedef struct _Player
{
	int id;				//玩家编号
	char name[20];		//玩家名字
	char password[20];	//密码
	double gold;			//游戏货币
	Bag bag;				//玩家的背包
	double sysee;			//游戏充值货币
}Player;

int propscount;
int playercount;
Prop* props;
Player* players;


void init();										//初始化游戏数据
void showprop();
void showplayer();
void trade(Player* player,int propId);										//交易

int main(){
	//初始化
	init();
	//显示
	showprop();
	showplayer();
	printf("--------------交易前--------------\n");

	trade(&players[1], 2);
	printf("--------------交易后--------------\n");
	//显示
	showprop();
	showplayer();

	return 0;
}

void init(){
	
	static Prop proarray[] = {
		{ 1,"剑", 3000, 20, "好剑" },
		{ 2,"刀", 3500, 30, "好刀" },
		{ 3,"枪", 2500, 19, "好枪" },
		{ 4,"棍", 3333, 10, "好棍" },
		{ 5,"斧", 4000, 2, "好斧头" },
	};
	propscount = sizeof(proarray) / sizeof(Prop);
	props = proarray;	

	static Player playarray[] = {
		{ 1, "shadow", "123456",50000 },
		{ 2, "fat", "123456", 150000 },
		{ 3, "god", "123456", 250000 },
		{ 4, "undertaker", "123456", 350000 },
	};
	playercount = 4;
	players = playarray;
}

void showprop(){
	int i = 0;
	if (props == NULL)
		return;
	printf("编号\t名称\t单价\t库存\t描述\n");
	for (i = 0; i < propscount;i++)
	{
		printf("%d\t%s\t%.2lf\t%d\t%s\n", props[i].id, props[i].name, props[i].price, props[i].stock, props[i].desc);
	}
}

void showplayer(){
	int i = 0;
	if (players == NULL)
		return;
	printf("编号\t%-15s金币\n","姓名");
	for (i = 0; i < playercount; i++)
	{
		printf("%d\t%-15s%.0lf\n", players[i].id, players[i].name, players[i].gold);
	}
}

void trade(Player* player, int propId){
	int i;
	//需要判断商品库存和玩家余额以及玩家背包空间
	Prop* treadprop = NULL;				//要购买的商品指针
	for (int i = 0; i < propscount;i++)
	{
		if (propId == props[i].id){
			treadprop = &props[i];
			break;
		}
	}
	if (treadprop->stock <= 0){
		printf("库存不足\n");
		return;
	}
	if (player->gold < treadprop->price)
	{
		printf("余额不足\n");
		return;
	}
	if (player->bag.count >= player->bag.max)
	{
		printf("没有足够的空间来存放\n");
		return;
	}
	//执行交易
	treadprop->stock--;
	player->gold -= treadprop->price;
	//判断玩家背包中是否已有该商品。
	for (i = 0; i < player->bag.count;i++)
	{
		if (propId = player->bag.props[i].id){
			player->bag.props[i].stock++;
			break;
		}
	}
	if (i == player->bag.count)			
	{
		//没有找到该商品，创建这个商品，并且是player->bag.count个元素
		int newindex = player->bag.count;
		player->bag.props[newindex].id = treadprop->id;
		strcpy(player->bag.props[newindex].name,treadprop->name);
		player->bag.props[newindex].price = treadprop->price;
		player->bag.props[newindex].stock = 1;
		strcpy(player->bag.props[newindex].desc, treadprop->desc);
		player->bag.count++;				//这里才+1
	}
}





