#include "YamanoteLineDB.h"
#include <stdio.h>
#include <string.h>

int main()
{
	// ��Ԃ���w����ۑ�����ϐ�
	char entry_station_name[MAX_STATION_NAME_LENGTH] = { '\0' };

	// ��ԉw�̗v�f�ԍ���ۑ�����ϐ�
	__int8  entry_station_index = 0;

	// �~�Ԃ���w����ۑ�����ϐ�
	char exit_station_name[MAX_STATION_NAME_LENGTH] = { '\0' };

	// �~�ԉw�̗v�f��ۑ�����ϐ�
	__int8  exit_station_index = 0;

	// �w�������������ǂ�����ێ�����ϐ�
	bool found_station = false;

	// �R����̈���̎���
	__int8 yamanote_total_time = 0;

	// �E����̍��v���� (��)
	__int8 right_total_time = 0;

	// ������̍��v���� (��)
	__int8 left_total_time = 0;



	// �R����̏�ԉw����E�����̃e�[�u��
	Station yamanote_right_table[YAMANOTE_STATION_NUM];

	// �R����̏�ԉw����̍������̃e�[�u��
	Station yamanote_left_table[YAMANOTE_STATION_NUM];

	// �R����̏�ԉw���獶���ł���������ʂ�e�[�u��
	Station yamanote_left_through_chuo_table[YAMANOTE_STATION_NUM + CHUO_STATION_NUM];

	// �R����̏�ԉw����E���ł���������ʂ�e�[�u��
	Station yamanote_right_through_chuo_table[YAMANOTE_STATION_NUM + CHUO_STATION_NUM];


	////////// ��ԉw�m�F /////////////////////
	while (true)
	{
		printf("��ԉw����͂��Ă�������\n");

		// ��Ԃ���w�����
		scanf_s("%s", entry_station_name, MAX_STATION_NAME_LENGTH);


		for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
		{
			// DB�ɉw����������
			if (!strcmp(g_YamanoteDB[i].m_StationName, entry_station_name)) {
				printf("��ԉw -> %s \n", &entry_station_name);
				found_station = true;

				// �v�f��ۑ�
				entry_station_index = i;
				break;
			}
		}

		// �������������烋�[�v�𔲂���
		if (found_station)break;

		printf("������܂���B������x���͂��Ă��������B\n");
	}


	////////// �~�ԉw�m�F /////////////////////
	found_station = false;
	while (true)
	{
		printf("�~�ԉw����͂��Ă�������\n");

		// �~�Ԃ���w�����
		scanf_s("%s", exit_station_name, MAX_STATION_NAME_LENGTH);

		for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
		{
			// ��ԉw�e�[�u������̍~�ԉw��T��
			if (!strcmp(g_YamanoteDB[i].m_StationName, exit_station_name)) {
				printf("�~�ԉw -> %s \n", &exit_station_name);
				found_station = true;

				// �v�f��ۑ�
				exit_station_index = i;
				break;
			}
		}
		// �������������烋�[�v�𔲂���
		if (found_station)break;

		// else ������x����
		printf("������܂���B������x���͂��Ă��������B \n");
	}



	// �e�e�[�u�����쐬



	// �e�e�[�u���ɂ����鎞�Ԃ��Z�o



	// ���ꂼ����o��


	return 0;
}
