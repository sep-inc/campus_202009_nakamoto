#ifndef SAFE_DELETE_H_
#define SAFE_DELETE_H_

// �Z�[�t�f���[�g
#define SAFE_DELETE(p) { if (p != nullptr) { delete (p); (p) = nullptr; }}

#endif