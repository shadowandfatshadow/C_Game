/*��Ʒ-����-���*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*��Ʒ�ṹ*/
typedef struct _Prop
{
	int id;				//����Ψһ�ı��
	char name[20];		//������
	double price;			//���ߵ���
	int stock;			//�����
	char desc[50];		//˵��
}Prop;

/*�����ṹ*/
typedef struct _Bag
{
	int playerId;			//������ҵ�id
	int count;			//��ǰ�����е��ߵ�����
	int max = 8;				//�����Ĳ������-����ͨ����ֵ��������
	Prop props[8];		//��ǰ�����еĵ�������
}Bag;


/*��ҽṹ*/
typedef struct _Player
{
	int id;				//��ұ��
	char name[20];		//�������
	char password[20];	//����
	double gold;			//��Ϸ����
	Bag bag;				//��ҵı���
	double sysee;			//��Ϸ��ֵ����
}Player;

int propscount;
int playercount;
Prop* props;
Player* players;


void init();										//��ʼ����Ϸ����
void showprop();
void showplayer();
void trade(Player* player,int propId);										//����

int main(){
	//��ʼ��
	init();
	//��ʾ
	showprop();
	showplayer();
	printf("--------------����ǰ--------------\n");

	trade(&players[1], 2);
	printf("--------------���׺�--------------\n");
	//��ʾ
	showprop();
	showplayer();

	return 0;
}

void init(){
	
	static Prop proarray[] = {
		{ 1,"��", 3000, 20, "�ý�" },
		{ 2,"��", 3500, 30, "�õ�" },
		{ 3,"ǹ", 2500, 19, "��ǹ" },
		{ 4,"��", 3333, 10, "�ù�" },
		{ 5,"��", 4000, 2, "�ø�ͷ" },
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
	printf("���\t����\t����\t���\t����\n");
	for (i = 0; i < propscount;i++)
	{
		printf("%d\t%s\t%.2lf\t%d\t%s\n", props[i].id, props[i].name, props[i].price, props[i].stock, props[i].desc);
	}
}

void showplayer(){
	int i = 0;
	if (players == NULL)
		return;
	printf("���\t%-15s���\n","����");
	for (i = 0; i < playercount; i++)
	{
		printf("%d\t%-15s%.0lf\n", players[i].id, players[i].name, players[i].gold);
	}
}

void trade(Player* player, int propId){
	int i;
	//��Ҫ�ж���Ʒ�����������Լ���ұ����ռ�
	Prop* treadprop = NULL;				//Ҫ�������Ʒָ��
	for (int i = 0; i < propscount;i++)
	{
		if (propId == props[i].id){
			treadprop = &props[i];
			break;
		}
	}
	if (treadprop->stock <= 0){
		printf("��治��\n");
		return;
	}
	if (player->gold < treadprop->price)
	{
		printf("����\n");
		return;
	}
	if (player->bag.count >= player->bag.max)
	{
		printf("û���㹻�Ŀռ������\n");
		return;
	}
	//ִ�н���
	treadprop->stock--;
	player->gold -= treadprop->price;
	//�ж���ұ������Ƿ����и���Ʒ��
	for (i = 0; i < player->bag.count;i++)
	{
		if (propId = player->bag.props[i].id){
			player->bag.props[i].stock++;
			break;
		}
	}
	if (i == player->bag.count)			
	{
		//û���ҵ�����Ʒ�����������Ʒ��������player->bag.count��Ԫ��
		int newindex = player->bag.count;
		player->bag.props[newindex].id = treadprop->id;
		strcpy(player->bag.props[newindex].name,treadprop->name);
		player->bag.props[newindex].price = treadprop->price;
		player->bag.props[newindex].stock = 1;
		strcpy(player->bag.props[newindex].desc, treadprop->desc);
		player->bag.count++;				//�����+1
	}
}





