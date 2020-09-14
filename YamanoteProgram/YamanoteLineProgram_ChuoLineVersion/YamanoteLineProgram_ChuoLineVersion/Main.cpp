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

	// �E���̍��v���� (��)
	__int8 right_total_time = 0;

	// �����̍��v���� (��)
	__int8 left_total_time = 0;

	// �������𗘗p�����E���ɂ����鎞��(��)
	__int8 chuo_right_total_time = 0;

	// �������𗘗p���������ɂ����鎞��(��)
	__int8 chuo_left_total_time = 0;



	// �R����̏�ԉw����E�����̃e�[�u��
	Station yamanote_right_table[YAMANOTE_STATION_NUM] = { 0 };

	// �R����̏�ԉw����̍������̃e�[�u��
	Station yamanote_left_table[YAMANOTE_STATION_NUM] = { 0 };

	// �R����̏�ԉw���獶���ł���������ʂ�e�[�u��
	Station yamanote_left_through_chuo_table[YAMANOTE_STATION_NUM + CHUO_STATION_NUM] = { 0 };

	// �R����̏�ԉw����E���ł���������ʂ�e�[�u��
	Station yamanote_right_through_chuo_table[YAMANOTE_STATION_NUM + CHUO_STATION_NUM] = { 0 };


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




	////////////////////////////////// �e�e�[�u�����쐬 /////////////////////////////////////////////
	
	/////////////////////////////////// �E���̃e�[�u�����쐬 //////////////////////////////////////////
	__int8 current_station_index = entry_station_index;
	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		// �����ړI�n�Ȃ�e�[�u���쐬�I��
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, exit_station_name)) break;

		yamanote_right_table[i] = g_YamanoteDB[current_station_index];
		
		current_station_index++;
		// ���݂̗v�f����DB�̗v�f���𒴂����ꍇ0�ɂ���
		if (current_station_index >= YAMANOTE_STATION_NUM) current_station_index = 0;
	}


	/////////////////////////////////// �����̃e�[�u�����쐬 //////////////////////////////////////////
	current_station_index = entry_station_index;
	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		// �����ړI�n�Ȃ�e�[�u���쐬�I��
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, exit_station_name)) break;

		yamanote_left_table[i] = g_YamanoteDB[current_station_index];


		current_station_index--;
		// ���݂̗v�f����0�������ɂȂ�����DB�̍Ō�̗v�f�ɂ���
		if (current_station_index < 0) current_station_index = YAMANOTE_INDEX_NUM;
	}

	
	//////////////////////////////////////// �������𗘗p�����E���̃e�[�u�����쐬 //////////////////////////////////////////

	// ���݂̉w�̃C���f�b�N�X��ێ�����ϐ�
	current_station_index = entry_station_index;

	// �V�������e�[�u���̗v�f
	__int8 new_table_index = 0;

	// �������𔲂�����ɉE�����̂ǂ���ɂ�������ۑ�����ϐ�
	// true -> �E    false -> ��
	bool is_right = true;

	while (true)
	{
		// �����ړI�n�Ȃ�e�[�u���쐬�I��
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, exit_station_name)) break;

		// �e�[�u���Ɍ��݂̉w��ǉ�����
		yamanote_right_through_chuo_table[new_table_index] = g_YamanoteDB[current_station_index];
		new_table_index++;
		
		/////////////////// ���݂̉w���V�h�Ȃ�
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, "�V�h"))
		{
			for (int i = 0; i < CHUO_STATION_NUM; ++i)
			{
				// �������̐_�c�܂ł�����
				if (!strcmp(g_ChuoLine[i].m_StationName, "�_�c"))
				{
					// �R����̐_�c���e�[�u���ɒǉ�����
					yamanote_right_through_chuo_table[new_table_index] = g_YamanoteDB[g_ChuoLine[i].m_StationId];
					new_table_index++;

					// ���݂̉w��_�c�ɐݒ肷��
					current_station_index = g_ChuoLine[i].m_StationId;
					break;
				}

				// �������̉w��ǉ�����
				yamanote_right_through_chuo_table[new_table_index] = g_ChuoLine[i];
				new_table_index++;
			}
			
			// ���݂̉w���ꎞ�ۑ�����
			__int8 temp_current_index = current_station_index;
			// �������𔲂������ƁA�E��肩����肩���ŒZ�����Ō��߂�
			for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
			{
				temp_current_index += i;

				// ���݂̉w���R���DB�̗v�f�𒴂�����0�ɖ߂��B
				if (temp_current_index >= YAMANOTE_STATION_NUM) temp_current_index = 0;

				// ��ԉw�ɗ�����
				if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, entry_station_name))
				{
					// �����ɍ~�ԉw������
					is_right = false;
					current_station_index--;

					// ���݂̉w���R���DB�̗v�f�����������v�f�̍ő�ɖ߂�
					if (current_station_index < 0)current_station_index = YAMANOTE_INDEX_NUM;
					break;
				}
				// �~�ԉw�ɗ�����
				else if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, exit_station_name))
				{
					// �E���ɍ~�ԉw��
					is_right = true;
					current_station_index++;

					// ���݂̉w���R���DB�̗v�f�𒴂�����0�ɖ߂��B
					if (current_station_index >= YAMANOTE_STATION_NUM) current_station_index = 0;
					break;
				}

			}
		}


		////////////// ���݂̉w���_�c�Ȃ�
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, "�_�c"))
		{
			for (int i = 3; i >= 0; --i)
			{
				// �������̐V�h�܂ł�����
				if (!strcmp(g_ChuoLine[i].m_StationName, "�V�h"))
				{
					// �R����̐V�h���e�[�u���ɒǉ�����
					yamanote_right_through_chuo_table[new_table_index] = g_YamanoteDB[g_ChuoLine[i].m_StationId];
					new_table_index++;

					// ���݂̉w��V�h�ɐݒ肷��
					current_station_index = g_ChuoLine[i].m_StationId;
					break;
				}

				// �������̉w��ǉ�����
				yamanote_right_through_chuo_table[new_table_index] = g_ChuoLine[i];
				new_table_index++;
			}

			// ���݂̉w���ꎞ�ۑ�����
			__int8 temp_current_index = current_station_index;
			// �������𔲂������ƁA�E��肩����肩���ŒZ�����Ō��߂�
			for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
			{
				temp_current_index += i;

				// ���݂̉w���R���DB�̗v�f�𒴂�����0�ɖ߂��B
				if (temp_current_index >= YAMANOTE_STATION_NUM) temp_current_index = 0;;

				// ��ԉw�ɗ�����
				if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, entry_station_name))
				{
					// �����ɍ~�ԉw������
					is_right = false;
					current_station_index--;

					// ���݂̉w���R���DB�̗v�f�����������v�f�̍ő�ɖ߂�
					if (current_station_index < 0)current_station_index = YAMANOTE_STATION_NUM - 1;
					break;
				}
				// �~�ԉw�ɗ�����
				else if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, exit_station_name))
				{
					// �E���ɍ~�ԉw��
					is_right = true;
					current_station_index++;

					// ���݂̉w���R���DB�̗v�f�𒴂�����0�ɖ߂��B
					if (current_station_index >= YAMANOTE_STATION_NUM) current_station_index = 0;
					break;
				}

			}
		}

		// �����ړI�n�Ȃ�e�[�u���쐬�I��
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, exit_station_name)) break;

		// �w��i�߂�
		if (is_right == true) {
			current_station_index++;
		}
		else {
			current_station_index--;
		}

		// ���݂̉w���R���DB�̗v�f�𒴂�����0�ɖ߂��B
		if (current_station_index >= YAMANOTE_STATION_NUM) current_station_index = 0;

		// ���݂̉w���R���DB�̗v�f�����������v�f�̍ő�ɖ߂�
		if (current_station_index < 0)current_station_index = YAMANOTE_INDEX_NUM;

	}


	////////////////////////////////////// �������𗘗p���������̃e�[�u�����쐬 //////////////////////////////////////////

	// ���݂̉w�̃C���f�b�N�X��ێ�����ϐ�
	current_station_index = entry_station_index;

	// �V�������e�[�u���̗v�f
	new_table_index = 0;

	// �������𔲂�����ɉE�����̂ǂ���ɂ�������ۑ�����ϐ�
	// true -> �E    false -> ��
	is_right = false;
	while (true)
	{

		// �����ړI�n�Ȃ�e�[�u���쐬�I��
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, exit_station_name)) break;

		// �e�[�u���Ɍ��݂̉w��ǉ�����
		yamanote_left_through_chuo_table[new_table_index] = g_YamanoteDB[current_station_index];
		new_table_index++;


		/////////////////// ���݂̉w���V�h�Ȃ�
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, "�V�h"))
		{
			for (int i = 0; i < CHUO_STATION_NUM; ++i)
			{
				// �������̐_�c�܂ł�����
				if (!strcmp(g_ChuoLine[i].m_StationName, "�_�c"))
				{
					// �R����̐_�c���e�[�u���ɒǉ�����
					yamanote_left_through_chuo_table[new_table_index] = g_YamanoteDB[g_ChuoLine[i].m_StationId];
					new_table_index++;

					// ���݂̉w��_�c�ɐݒ肷��
					current_station_index = g_ChuoLine[i].m_StationId;
					break;
				}

				// �������̉w��ǉ�����
				yamanote_left_through_chuo_table[new_table_index] = g_ChuoLine[i];
				new_table_index++;
			}

			// ���݂̉w���ꎞ�ۑ�����
			__int8 temp_current_index = current_station_index;
			// �������𔲂������ƁA�E��肩����肩���ŒZ�����Ō��߂�
			for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
			{
				temp_current_index += i;

				// ���݂̉w���R���DB�̗v�f�𒴂�����0�ɖ߂��B
				if (temp_current_index >= YAMANOTE_STATION_NUM) temp_current_index = 0;;

				// ��ԉw�ɗ�����
				if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, entry_station_name))
				{
					// �����ɍ~�ԉw������
					is_right = false;
					break;
				}
				// �~�ԉw�ɗ�����
				else if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, exit_station_name))
				{
					// �E���ɍ~�ԉw��
					is_right = true;
					break;
				}

			}
		}


		////////////// ���݂̉w���_�c�Ȃ�
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, "�_�c"))
		{
			for (int i = CHUO_INDEX_NUM; i >= 0; --i)
			{
				// �������̐V�h�܂ł�����
				if (!strcmp(g_ChuoLine[i].m_StationName, "�V�h"))
				{
					// �R����̐V�h���e�[�u���ɒǉ�����
					yamanote_left_through_chuo_table[new_table_index] = g_YamanoteDB[g_ChuoLine[i].m_StationId];
					new_table_index++;

					// ���݂̉w��V�h�ɐݒ肷��
					current_station_index = g_ChuoLine[i].m_StationId;
					break;
				}

				// �������̉w��ǉ�����
				yamanote_left_through_chuo_table[new_table_index] = g_ChuoLine[i];
				new_table_index++;
			}

			// ���݂̉w���ꎞ�ۑ�����
			__int8 temp_current_index = current_station_index;
			// �������𔲂������ƁA�E��肩����肩���ŒZ�����Ō��߂�
			for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
			{
				temp_current_index += i;

				// ���݂̉w���R���DB�̗v�f�𒴂�����0�ɖ߂��B
				if (temp_current_index >= YAMANOTE_STATION_NUM) temp_current_index = 0;;

				// ��ԉw�ɗ�����
				if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, entry_station_name))
				{
					// �����ɍ~�ԉw������
					is_right = false;
					break;
				}
				// �~�ԉw�ɗ�����
				else if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, exit_station_name))
				{
					// �E���ɍ~�ԉw��
					is_right = true;

					break;
				}

			}
		}

		// �����ړI�n�Ȃ�e�[�u���쐬�I��
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, exit_station_name)) break;

		// �w��i�߂�
		if (is_right == true) {
			current_station_index++;
		}
		else {
			current_station_index--;
		}

		// ���݂̉w���R���DB�̗v�f�𒴂�����0�ɖ߂��B
		if (current_station_index >= YAMANOTE_STATION_NUM) current_station_index = 0;

		// ���݂̉w���R���DB�̗v�f�����������v�f�̍ő�ɖ߂�
		if (current_station_index < 0)current_station_index = YAMANOTE_INDEX_NUM;

	}



	////////////////////////////////////////////// �e�e�[�u���ɂ����鎞�Ԃ��Z�o /////////////////////////////////////////////////////

	// �E���̎��Ԃ��Z�o
	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		right_total_time += yamanote_right_table[i].m_NextStationCost;
	}

	// �����̎��Ԃ��o��
	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		left_total_time += yamanote_left_table[i].m_NextStationCost;
	}

	// �E���̒�������ʂ鎞��
	for (int i = 0; i < YAMANOTE_STATION_NUM + CHUO_STATION_NUM; ++i)
	{
		chuo_right_total_time += yamanote_right_through_chuo_table[i].m_NextStationCost;
	}

	// �����̒�������ʂ鎞��
	for (int i = 0; i < YAMANOTE_STATION_NUM + CHUO_STATION_NUM; ++i)
	{
		chuo_left_total_time += yamanote_left_through_chuo_table[i].m_NextStationCost;
	}

	// ���ꂼ����o��
	printf("%s  ->  %s  �ɂ����鎞��\n", entry_station_name, exit_station_name);
	printf("�E���ɂ����鎞�Ԃ� %d �ł��B\n", right_total_time);
	printf("�����ɂ����鎞�Ԃ� %d �ł��B\n", left_total_time);
	printf("�������𗘗p�����E���ɂ����鎞�Ԃ� %d �ł��B\n", chuo_right_total_time);
	printf("�������𗘗p���������ɂ����鎞�Ԃ� %d �ł��B\n", chuo_left_total_time);


	return 0;
}
