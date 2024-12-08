# Teamproject2

## UpdateNote
v0.1: 
	ActionStatus �߰�
	PlayerStatus �߰�
v0.2:
	Animation �߰�

v0.3:
	RectEX2 사용해서 박스충돌 마무리
	Line추가
	


## �÷��̾��� �浹���� ��ü
1. ����(��������)
2. �ڽ�(��������)
3. ����
4. �߻�ü(������)
5. ������(ȿ�� ����) 

## ������ �浹���� ��ü
1. ����(��������)
2. �ڽ�(��������)
3. �÷��̾�
4. �߻�ü(������)

## �������� �浹���� ��ü
1. ����(��������)
2. �ڽ�(��������)
3. �÷��̾�

## �ڽ��� �浹���� ��ü
1. �÷��̾�
2. ����
3. ������

���

��ٸ�

������ �ִ°� 
��ȣ�ۿ�(�ڽ�);
## Platform
	Line, Box, 

## Monster
	����, �ź���, ����



## �ϴ� �������� ���� ������ ���߱�

Box������ ������ ������
Player.m_tInfo.fCY * 0.5f ���� ũ�ų� ������ ������_

## �¿� ��ġ������ �׻� �ӵ��� �Ȱ��� �ؾ� �����̰� ���Ͼ


## OBJECT ID
```
enum OBJID { OBJ_NONE, OBJ_PLAYER, OBJ_MONSTER, OBJ_ITEM, OBJ_BOX, OBJ_LINE, OBJ_END };
```
## TAG
```
enum TAG { TAG_NONE, TAG_LINE, TAG_WALL, TAG_FLOOR, TAG_END };
```
## OBJECT STATUS
```
enum OBJSTATUS { OBJ_NOEVENT =0,_ OBJ_DEAD_};
```
## PLAYER STATUS
```
enum PLAYERSTATUS { PS_SMALL_, PS_BIG, PS_FIRE, PS_STAR, PS_END };
```
## ACTION STATUS
```
enum ACTIONSTATUS { AS_STOP, AS_MOVE_LEFT, AS_MOVE_RIGHT, AS_FALL, AS_JUMP, AS_END };
```
## FACING DIRECTION
```
enum FACING { LEFT, RIGHT }
```

## ITEMTYPE
```
enum ITEMTYPE { ITEM_NONE, ITEM_MUSHROOM, ITEM_FLOWER, ITEM_STAR, ITEM_CLEAR, ITEM_END };
```
## BOXTYPE
```
enum BOXTYPE {BOX_NONE, BOX_BREAK, BOX_ITEM, BOX_END };
```