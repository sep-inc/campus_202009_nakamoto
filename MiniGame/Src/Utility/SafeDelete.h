#ifndef SAFE_DELETE_H_
#define SAFE_DELETE_H_

// セーフデリート
#define SAFE_DELETE(p) { if (p != nullptr) { delete (p); (p) = nullptr; }}

#endif