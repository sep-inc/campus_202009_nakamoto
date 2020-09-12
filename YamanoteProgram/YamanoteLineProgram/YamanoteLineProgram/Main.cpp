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

	
	/* ��ԉw�m�F */
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


	/* �~�ԉw�m�F */
		////////// �~�ԉw�m�F /////////////////////
	found_station = false;
	while (true)
	{
		printf("�~�ԉw����͂��Ă�������\n");

		// �~�Ԃ���w�����
		scanf_s("%s", exit_station_name, MAX_STATION_NAME_LENGTH);

		for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
		{
			// DB�ɉw����������
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


	// ��ԉw����̉E���̃e�[�u�������
	// ��ԉw�̗v�f���擾
	__int8 index = entry_station_index;
	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		yamanote_right_table[i] = g_YamanoteDB[index];

		index++;
		// ���݂̗v�f����DB�̗v�f���𒴂����ꍇ0�ɂ���
		if (index >= YAMANOTE_STATION_NUM) index = 0;
	}

	// ��ԉw����̍����̃e�[�u�������
	// ��ԉw�̗v�f���擾
	index = entry_station_index;
	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		yamanote_left_table[i] = g_YamanoteDB[index];

		index--;
		// ���݂̗v�f����0�������ɂȂ�����DB�̍Ō�̗v�f�ɂ���
		if (index < 0) index = YAMANOTE_STATION_NUM - 1;
	}


	// �E���̎��Ԃ��v��
	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		if (!strcmp(yamanote_right_table[i].m_StationName, exit_station_name))
		{
			break;
		}

		right_total_time += yamanote_right_table[i].m_NectStationCost;
	}

	// �����̎��Ԃ��v��
	for (int i = 1; i < YAMANOTE_STATION_NUM; ++i)
	{
		left_total_time += yamanote_left_table[i].m_NectStationCost;

		if (!strcmp(yamanote_left_table[i].m_StationName, exit_station_name))
		{
			break;
		}
	}


	// ���ʂ��o��
	printf("%s -> %s\n", entry_station_name, exit_station_name);
	printf("�E���ɂ����鎞�Ԃ�[ %d ]���ł�\n", right_total_time);
	printf("�����ɂ����鎞�Ԃ�[ %d ]���ł�\n", left_total_time);


	// �v���O�����I��
	return 0;
}