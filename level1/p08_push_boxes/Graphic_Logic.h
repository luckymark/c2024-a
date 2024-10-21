#pragma once
#ifndef GRAPHIC_LOGIC_H
#define GRAPHIC_LOGIC_H 1
#include <vector>
/*
 * �����߼���
 * ��Ϸ�����СΪ800*600������ÿ�������СΪ50*50��������ÿգ���ͼ���Ϊ14*10
 * 0����յأ�1�������ӣ�2����Ŀ�ĵأ�4�����ˣ�8����ǽ��ʹ��λ������ǿ�ɶ���
 * ���磬������Ŀ�ĵ���Ϊ1 | 2 = 3������Ŀ�ĵ���Ϊ4 | 2 = 6
 * ����Ȼ˵���д�����ɶ���Ҳ��ʷһ�������ˣ�
 */
class Graphic_Logic {
public:
	Graphic_Logic();
	~Graphic_Logic();
	void menu();
	//�ȼٶ���10��
	int level();
	bool pass();
	void has_ended();
private:
	//����������ÿգ�x��ΧΪ1-14��y��ΧΪ1-10
	void draw(int type, int x, int y);
public:
	void init_level(const std::vector<std::vector<int>> &level);
	//���ڽ��еĹؿ�����0����˵�
	int level_playing;
};
#endif // GRAPHIC_LOGIC_H