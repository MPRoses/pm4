//file stapel.h
class stapel {
private:
    int arr[400]; // max board size 20x20, predefined zodat geen vectors gebruikt hoeven worden
    int plek = 0;
    int grootte;
public:
    static int breedte;
    static int hoogte;
    void reset();
    void voegZetToe(int kolom);
    int neemZetTerug();
    void printArray();
};
