#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <vector>
#include <time.h>

// �f�[�^�̗v�f��
#define DATA_NUM 10


struct SomeData
{
	__int8 m_Number;
	__int8 m_Id;
}; 


// 10�̔z���0�`100(���Ȃ�)�ŏ��������ĕԂ���
SomeData* RandPerm();

// �����\�[�g�֐�
void AscendingSort(SomeData* data_, int indexNum_);

// ����a_��b_�����ւ���֐�
void Swap(__int8* a_, __int8* b_);

// �o��
void Print(SomeData* data_, int indexNum_);

/*===============MAIN================*/
int main()
{
	// ���������[�N���o�p
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ��������
	srand((unsigned int)time(nullptr));

	// �������擾
	SomeData* hoge = RandPerm();

	// null�`�F�b�N
	if (hoge == nullptr) return -1;

	/****** �\�[�g�O ******/
	printf("-----Befor-----\n");

	Print(hoge, DATA_NUM);

	printf("---------------\n");

	/****** �\�[�g ******/
	AscendingSort(hoge, DATA_NUM);

	/****** �\�[�g��̒l��\�� ******/
	printf("-----Affter-----\n");

	Print(hoge, DATA_NUM);

	printf("---------------\n");


	// ���
	free(hoge);
	getchar();


	return 0;
}


SomeData* RandPerm()
{
	// �߂�l�p�̃f�[�^���m��
	SomeData* ret_data = (SomeData*)malloc(sizeof(SomeData) * DATA_NUM);
	// �f�[�^�̏�����
	for (int i = 0; i < DATA_NUM; ++i) {
		// �S��-1�ŏ�����
		ret_data[i].m_Number = -1;
		// 1�Ԃ���ID��U���Ă���
		ret_data[i].m_Id = i + 1;
	}

	// ���݂ǂ��̃f�[�^�܂ł����Ă��邩���J�E���g����ϐ�
	int count = 0;
	while (count != DATA_NUM)
	{
		// 0����100�܂ł̗������擾����
		int random_num = rand() % 101;
		for (int j = 0; j <= count; ++j)
		{
			// ���������_���łł��l�����łɔz��ɂ������ꍇ
			if (ret_data[j].m_Number == random_num) {
				break;
			}

			// �Ō�܂ŒT���ē��������Ȃ������ꍇ
			if (j == count) {
				// �ǉ�����
				ret_data[count].m_Number = random_num;
				count++;
				break;
			}
		}
	}

	return ret_data;
}

void AscendingSort(SomeData* data_, int indexNum_)
{
	for (int i = 0; i < indexNum_; ++i){
		for (int j = i+1; j < indexNum_; ++j){

			// ���݂̗v�f i �� ���̗v�f���r���Č��݂̗v�f�̕����傫����Γ���ւ���
			if (data_[i].m_Number > data_[j].m_Number) {
				Swap(&data_[i].m_Number, &data_[j].m_Number);
			}

		}
	}
}

void Swap(__int8* a_, __int8* b_)
{
	int temp = *a_;
	*a_ = *b_;
	*b_ = temp;
}

void Print(SomeData* data_, int indexNum_)
{
	for (int i = 0; i < indexNum_; ++i) {
		printf("id = %d\tnum = %d\n", data_[i].m_Id, data_[i].m_Number);
	}
}

