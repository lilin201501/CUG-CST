#include <iomanip>
#include <iostream>

using namespace std;

enum class status { freeZone, usedZone };

class block {
   public:
    block() {}
    block(int _address, int _size, int _id, status _state, block* _pre,
          block* _next) {
        address = _address;
        size = _size;
        id = _id;
        state = _state;
        pre = _pre;
        next = _next;
    }
    int address;
    int size;
    int id;
    status state;  // ״̬
    block* pre;    // ǰ��ָ��
    block* next;   // ����ָ��
};

class distrabuteArea {
   public:
    distrabuteArea() {}
    block* head = new block();
};

distrabuteArea* blocks = new distrabuteArea();

void intdisArea() {
    blocks->head->pre = nullptr;
    blocks->head->next =
        new block(0, 512, -1, status::freeZone, nullptr, nullptr);
    blocks->head->next->pre = blocks->head;
}

bool firstFit(int id, int size) {
    block* p = blocks->head->next;
    while (p != nullptr) {
        //��ǰ����ռ��㹻�������СΪsize������
        if (p->state == status::freeZone && p->size >= size) {
            block* node = new block(p->address + size, p->size - size, -1,
                                    status::freeZone, p, p->next);
            // �޸ķ������ڵ�ָ��
            if (p->next != nullptr) p->next->pre = node;

            p->next = node;
            // �����������
            p->size = size;
            p->state = status::usedZone;
            p->id = id;

            return true;
        }
        p = p->next;
    }
    return false;
}

bool bestFit(int id, int size) {
    block* tar = nullptr;
    int tarSize = 512 + 1;
    block* p = blocks->head->next;
    // Ѱ����ѿ�������
    while (p != nullptr) {
        if (p->state == status::freeZone && p->size >= size &&
            p->size < tarSize) {
            tar = p;
            tarSize = p->size;
        }
        p = p->next;
    }

    // �ҵ�Ҫ����Ŀ��з����������СΪsize������
    if (tar != nullptr) {
        block* node = new block(tar->address + size, tar->size - size, -1,
                                status::freeZone, tar, tar->next);
        if (tar->next != nullptr) tar->next->pre = node;
        // �����������
        tar->next = node;
        tar->size = size;
        tar->state = status::usedZone;
        tar->id = id;
        return true;
    } else {
        return false;
    }
}

int worstFit(int id, int size) {
    block* tar = nullptr;
    int tarSize = 512 + 1;
    block* p = blocks->head->next;
    int tempsize = 0;
    // Ѱ������������
    while (p != nullptr) {
        
        if (p->state == status::freeZone && p->size >= tempsize) {
            tar = p;
            tarSize = p->size;
            tempsize = p->size;
        }
        p = p->next;
    }

    // �ҵ�Ҫ����Ŀ��з���
    if (tar != nullptr && tarSize >= size) {
        block* node = new block(tar->address + size, tar->size - size, -1,
                                status::freeZone, tar, tar->next);
        if (tar->next != nullptr) tar->next->pre = node;
        // �����������
        tar->next = node;
        tar->size = size;
        tar->state = status::usedZone;
        tar->id = id;
        return true;
    } else {
        return false;
    }
}

int release(int id) {
    bool isFound = false;
    bool up = false;
    bool down = false;
    block *p = blocks->head->next, *focus;
    while (p != nullptr) {
        //�Ƿ��ҵ���ʹ�õ�id��
        if (p->state == status::usedZone && p->id == id) {
            isFound = true;

            // �����ǿ��з���
            if (p->pre != blocks->head && p->pre->state == status::freeZone) {
                up = true;
                focus = p;
                p = p->pre;
                p->size = p->size + focus->size;
                p->next = focus->next;
                if (focus->next != nullptr) focus->next->pre = p;
                free(focus);
            }

            // �����ǿ��з���
            if (p->next != nullptr && p->next->state == status::freeZone) {
                down = true;
                focus = p->next;
                p->size = p->size + focus->size;
                p->state = status::freeZone;
                p->id = -1;
                p->next = focus->next;
                if (focus->next != nullptr) focus->next->pre = p;
                free(focus);
            }

            if (!up && !down) {  // ���¶���ռ�÷���
                p->state = status::freeZone;
                p->id = -1;
            }
        }
        p = p->next;
    }
    return isFound;
}

void showMemory() {
    cout << "��ǰ���ڴ����������£�" << endl;
    cout << " ��ַ  "
         << " ��С   "
         << " ״̬ "
         << " ��ҵ��  " << endl;
    block* p = blocks->head->next;
    while (p != nullptr) {
        cout << setw(4) << 512-p->address << setw(8) << p->size << setw(8);
        if (p->state == status::freeZone)
            cout << "����";
        else
            cout << "ռ��";
        cout << setw(5) << p->id << endl;
        p = p->next;
    }
}

void showMenu() {
    cout << "��ѡ��Ҫ���õķ��ò���" << endl;
    cout << "1.�״���Ӧ�㷨" << endl;
    cout << "2.�����Ӧ�㷨" << endl;
    cout << "3.���Ӧ�㷨" << endl;
}

void showAction() {
    cout << "������Ҫ���еĲ���" << endl;
    cout << "1. �������\n2. �ͷŷ���\n0. �˳�" << endl;
}

void showExcuFailed() {
    cout << "Execution Failed��" << endl;
}

void dynamicPartition() {
    int selection, option;
    int id, size = 0;
    intdisArea();
    showMenu();
    cin >> selection;
    while (true) {
        showAction();
        cin >> option;
        if (option == 0) break;
        if (option == 1) {
            cout << "��������ҵ�ź�������ڴ��С��" << endl;
            cin >> id >> size;
            size++;
            if (selection == 1 && !firstFit(id, size))showExcuFailed();
            if (selection == 2 && !bestFit(id, size)) showExcuFailed();
            if (selection == 3 && !worstFit(id, size))showExcuFailed();
        }
        if (option == 2) {
            cout << "������Ҫ���յ���ҵ�ţ�" << endl;
            cin >> id;
            release(id);
        }
        showMemory();
    }
}
