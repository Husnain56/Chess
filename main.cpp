#include <iostream>
#include <SFML/Graphics.hpp>
#include "chessboard.h"
using namespace std;
using namespace sf;

int PawnPromotion();
class Piece
{

public:
    char color;
    Texture Piecetxt;
    Sprite Chesspiece;
    bool flag = true;

    virtual void SetTexture()
    {
    }
    virtual bool CheckValidMoves(Piece* arr[8][8], int, int, int, int) {
        return false;
    }
    virtual bool Capture(Piece* arr[8][8], int, int, int, int) {
        return true;
    }
    char getColor() {
        return color;
    }
    void setColor(char c) {
        color = c;
    }
    virtual int getPiece() {
        return 0;
    }
    virtual bool IsKing() {
        return false;
    }
    virtual bool ValidMoveCheck(Piece* arr[8][8], int, int, int, int, int, int) {
        return false;
    }
    virtual bool CaptureCheck(Piece* arr[8][8], int, int, int, int, int, int) {
        return false;
    }
    virtual bool CaptureCheck_(Piece* arr[8][8], int, int, int, int, int, int) {
        return false;
    }
    virtual bool ValidMoveCheck_(Piece* arr[8][8], int i, int j, int i1, int j1, int kx, int ky) {
        return false;
    }
    virtual bool PossibleMoves(Piece* arr[8][8], int, int, int, int) {
        return false;
    }
    virtual bool isPawn()
    {
        return false;
    }
};


bool IsCheck(Piece* arr[8][8], int kx, int ky);

class Pawns : public Piece
{

public:

    Pawns()
    {
        color = '\0';
    }
    Pawns(char ch)
    {
        color = ch;
    }
    bool isPawn()
    {
        return true;
    }
    virtual void SetTexture()
    {
        if (color == 'b')
        {

            if (!Piecetxt.loadFromFile("pieces/p1.png"))
            {
            }
        }
        else
        {
            if (!Piecetxt.loadFromFile("pieces/p7.png"))
            {
            }
        }
        Chesspiece.setTexture(Piecetxt);
    }
    virtual bool CheckValidMoves(Piece* arr[8][8], int i, int j, int i1, int j1) {


        if (i == 1 || i == 6) {
            if (this != nullptr && this->color == 'w') {
                if (j1 == j && i1 == i + 1) {
                    return true;
                }
                else if (j1 == j && i1 == i + 2 && arr[i + 1][j] == nullptr) {
                    return true;
                }
            }
            else {
                if (j1 == j && i1 == i - 1) {
                    return true;
                }
                else if (j1 == j && i1 == i - 2 && arr[i - 1][j] == nullptr) {
                    return true;
                }
            }
        }
        else {
            if (this != nullptr && this->color == 'w') {
                if (j1 == j && i1 == i + 1) {
                    return true;
                }
            }
            else {
                if (j1 == j && i1 == i - 1) {
                    return true;
                }
            }
        }
        return false;
    }
    virtual bool Capture(Piece* arr[8][8], int i, int j, int i1, int j1) {


        if (this != nullptr && this->color == 'w') {
            if ((i1 == i + 1 && (j1 == j - 1 || j1 == j + 1)) && arr[i1][j1] != nullptr && arr[i1][j1]->getColor() == 'b') {
                return true;
            }
        }
        else {
            if ((i1 == i - 1 && (j1 == j - 1 || j1 == j + 1)) && arr[i1][j1] != nullptr && arr[i1][j1]->getColor() == 'w') {
                return true;
            }
        }
        return false;
    }
    virtual bool ValidMoveCheck(Piece* arr[8][8], int i, int j, int i1, int j1, int kx, int ky) {
        flag = false;
        if (this->CheckValidMoves(arr, i, j, i1, j1)) {
            arr[i1][j1] = arr[i][j];
            arr[i][j] = nullptr;
            if (!IsCheck(arr, kx, ky)) {
                flag = true;
            }
            else {
                arr[i][j] = arr[i1][j1];
                arr[i1][j1] = nullptr;
            }
        }

        else {
            return false;
        }


        return flag;
    }
    bool CaptureCheck(Piece* arr[8][8], int i, int j, int i1, int j1, int kx, int ky) {
        flag = false;
        if (arr[i1][j1]->IsKing()) {
            return false;
        }
        if (this->Capture(arr, i, j, i1, j1)) {
            Piece* ptr;
            ptr = arr[i1][j1];
            arr[i1][j1] = arr[i][j];
            arr[i][j] = nullptr;
            if (!IsCheck(arr, kx, ky)) {
                flag = true;
            }
            else {
                arr[i][j] = arr[i1][j1];
                arr[i1][j1] = ptr;

            }

        }
        else {
            return false;
        }

        return flag;
    }
    bool PossibleMoves(Piece* arr[8][8], int i, int j, int kx, int ky) {

        Piece* temp[8][8];
        for (int m = 0; m < 8; m++) {
            for (int n = 0; n < 8; n++) {
                temp[m][n] = arr[m][n];
            }
        }

        if (this->color == 'b') {
            if (i - 1 >= 0 && j - 1 >= 0) {
                if (arr[i - 1][j - 1] != nullptr && arr[i][j]->getColor() != arr[i - 1][j - 1]->getColor()) {
                    if (Capture(arr, i, j, i - 1, j - 1)) {
                        Piece* ptr;
                        ptr = temp[i - 1][j - 1];
                        temp[i - 1][j - 1] = temp[i][j];
                        temp[i][j] = nullptr;
                        if (!IsCheck(temp, kx, ky)) {
                            temp[i][j] = temp[i - 1][j - 1];
                            temp[i - 1][j - 1] = ptr;
                            return true;
                        }
                        temp[i][j] = temp[i - 1][j - 1];
                        temp[i - 1][j - 1] = ptr;
                    }
                }
            }
            if (i - 1 >= 0 && j + 1 < 8) {
                if (arr[i - 1][j + 1] != nullptr && arr[i][j]->getColor() != arr[i - 1][j + 1]->getColor()) {
                    if (Capture(arr, i, j, i - 1, j + 1)) {
                        Piece* ptr;
                        ptr = temp[i - 1][j + 1];
                        temp[i - 1][j + 1] = temp[i][j];
                        temp[i][j] = nullptr;
                        if (!IsCheck(temp, kx, ky)) {
                            temp[i][j] = temp[i - 1][j + 1];
                            temp[i - 1][j + 1] = ptr;
                            return true;
                        }
                        temp[i][j] = temp[i - 1][j + 1];
                        temp[i - 1][j + 1] = ptr;
                    }
                }
            }
            if (i - 1 >= 0) {
                if (arr[i - 1][j] == nullptr) {
                    if (CheckValidMoves(arr, i, j, i - 1, j)) {
                        Piece* ptr;
                        ptr = temp[i - 1][j];
                        temp[i - 1][j] = temp[i][j];
                        temp[i][j] = nullptr;
                        if (!IsCheck(temp, kx, ky)) {
                            temp[i][j] = temp[i - 1][j];
                            temp[i - 1][j] = ptr;
                            return true;
                        }
                        temp[i][j] = temp[i - 1][j];
                        temp[i - 1][j] = ptr;
                    }
                }
            }
        }

        if (this->color == 'w') {
            if (i + 1 < 8 && j - 1 >= 0) {
                if (arr[i + 1][j - 1] != nullptr && arr[i][j]->getColor() != arr[i + 1][j - 1]->getColor()) {
                    if (Capture(arr, i, j, i + 1, j - 1)) {
                        Piece* ptr;
                        ptr = temp[i + 1][j - 1];
                        temp[i + 1][j - 1] = temp[i][j];
                        temp[i][j] = nullptr;
                        if (!IsCheck(temp, kx, ky)) {
                            temp[i][j] = temp[i + 1][j - 1];
                            temp[i + 1][j - 1] = ptr;
                            return true;
                        }
                        temp[i][j] = temp[i + 1][j - 1];
                        temp[i + 1][j - 1] = ptr;
                    }
                }
            }
            if (i + 1 < 8 && j + 1 < 8) {
                if (arr[i + 1][j + 1] != nullptr && arr[i][j]->getColor() != arr[i + 1][j + 1]->getColor()) {
                    if (Capture(arr, i, j, i + 1, j + 1)) {
                        Piece* ptr;
                        ptr = temp[i + 1][j + 1];
                        temp[i + 1][j + 1] = temp[i][j];
                        temp[i][j] = nullptr;
                        if (!IsCheck(temp, kx, ky)) {
                            temp[i][j] = temp[i + 1][j + 1];
                            temp[i + 1][j + 1] = ptr;
                            return true;
                        }
                        temp[i][j] = temp[i + 1][j + 1];
                        temp[i + 1][j + 1] = ptr;
                    }
                }
            }
            if (i + 1 < 8) {
                if (arr[i + 1][j] == nullptr) {
                    if (CheckValidMoves(arr, i, j, i + 1, j)) {
                        Piece* ptr;
                        ptr = temp[i + 1][j];
                        temp[i + 1][j] = temp[i][j];
                        temp[i][j] = nullptr;
                        if (!IsCheck(temp, kx, ky)) {
                            temp[i][j] = temp[i + 1][j];
                            temp[i + 1][j] = ptr;
                            return true;
                        }
                        temp[i][j] = temp[i + 1][j];
                        temp[i + 1][j] = ptr;
                    }
                }
            }
        }


        return false;
    }
};

class Rook : public Piece
{

public:

    Rook()
    {
        color = '\0';
    }
    Rook(char ch)
    {
        color = ch;
    }
    virtual void SetTexture()
    {
        if (color == 'b')
        {

            if (!Piecetxt.loadFromFile("pieces/p2.png"))
            {
            }
        }
        else
        {
            if (!Piecetxt.loadFromFile("pieces/p8.png"))
            {
            }
        }
        Chesspiece.setTexture(Piecetxt);
    }
    virtual bool CheckValidMoves(Piece* arr[8][8], int i, int j, int i1, int j1) {

        int start, end;
        if (i1 == i || j1 == j) {
            if (i1 == i) {

                if (j1 > j) {
                    start = j + 1;
                    end = j1;
                }
                else {
                    start = j1 + 1;
                    end = j;
                }
                for (int col = start; col < end; col++) {
                    if (arr[i][col] != nullptr) {
                        return false;
                    }
                }
            }
            else if (j1 == j) {
                if (i1 > i) {
                    start = i + 1;
                    end = i1;
                }
                else {
                    start = i1 + 1;
                    end = i;
                }
                for (int row = start; row < end; row++) {
                    if (arr[row][j] != nullptr) {
                        return false;
                    }
                }
            }
            return true;
        }

        return false;
    }

    virtual bool Capture(Piece* arr[8][8], int i, int j, int i1, int j1)
    {

        int start, end;

        if ((this->color == 'w' && arr[i1][j1]->getColor() == 'b') || (this->color == 'b' && arr[i1][j1]->getColor() == 'w')) {
            if (i1 == i || j1 == j) {
                if (i1 == i) {

                    if (j1 > j) {
                        start = j + 1;
                        end = j1;
                    }
                    else {
                        start = j1 + 1;
                        end = j;
                    }
                    for (int col = start; col < end; col++) {
                        if (arr[i][col] != nullptr) {
                            return false;
                        }
                    }
                }
                else if (j1 == j) {
                    if (i1 > i) {
                        start = i + 1;
                        end = i1;
                    }
                    else {
                        start = i1 + 1;
                        end = i;
                    }
                    for (int row = start; row < end; row++) {
                        if (arr[row][j] != nullptr) {
                            return false;
                        }
                    }
                }
                return true;
            }
        }
        return false;
    }

    virtual bool ValidMoveCheck(Piece* arr[8][8], int i, int j, int i1, int j1, int kx, int ky) {
        flag = false;
        if (this->CheckValidMoves(arr, i, j, i1, j1)) {
            arr[i1][j1] = arr[i][j];
            arr[i][j] = nullptr;
            if (!IsCheck(arr, kx, ky)) {
                flag = true;
            }
            else {
                arr[i][j] = arr[i1][j1];
                arr[i1][j1] = nullptr;
            }
        }
        else {
            return false;
        }

        return flag;
    }
    bool CaptureCheck(Piece* arr[8][8], int i, int j, int i1, int j1, int kx, int ky) {
        flag = false;
        if (arr[i1][j1]->IsKing()) {
            return false;
        }
        if (this->Capture(arr, i, j, i1, j1)) {
            Piece* ptr;
            ptr = arr[i1][j1];
            arr[i1][j1] = arr[i][j];
            arr[i][j] = nullptr;
            if (!IsCheck(arr, kx, ky)) {
                flag = true;
            }
            else {
                arr[i][j] = arr[i1][j1];
                arr[i1][j1] = ptr;

            }

        }
        else {
            return false;
        }

        return flag;
    }
    bool PossibleMoves(Piece* arr[8][8], int i, int j, int kx, int ky) {

        Piece* temp[8][8];
        for (int m = 0; m < 8; m++) {
            for (int n = 0; n < 8; n++) {
                temp[m][n] = arr[m][n];
            }
        }

        //Rook

        for (int k = j + 1; k < 8; k++) {
            if (arr[i][k] != nullptr && arr[i][j]->getColor() != arr[i][k]->getColor()) {
                if (Capture(arr, i, j, i, k)) {

                    Piece* ptr;
                    ptr = temp[i][k];
                    temp[i][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i][k];
                        temp[i][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i][k];
                    temp[i][k] = ptr;
                }
            }
            else if (arr[i][k] == nullptr) {
                if (CheckValidMoves(arr, i, j, i, k)) {

                    Piece* ptr;
                    ptr = temp[i][k];
                    temp[i][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i][k];
                        temp[i][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i][k];
                    temp[i][k] = ptr;
                }
            }
        }

        for (int k = j - 1; k >= 0; k--) {

            if (arr[i][k] != nullptr && arr[i][j]->getColor() != arr[i][k]->getColor()) {
                if (Capture(arr, i, j, i, k)) {
                    Piece* ptr;
                    ptr = temp[i][k];
                    temp[i][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i][k];
                        temp[i][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i][k];
                    temp[i][k] = ptr;
                }
            }
            else if (arr[i][k] == nullptr) {
                if (CheckValidMoves(arr, i, j, i, k)) {
                    Piece* ptr;
                    ptr = temp[i][k];
                    temp[i][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i][k];
                        temp[i][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i][k];
                    temp[i][k] = ptr;
                }
            }
        }

        for (int k = i + 1; k < 8; k++) {

            if (arr[k][j] != nullptr && arr[i][j]->getColor() != arr[k][j]->getColor()) {
                if (Capture(arr, i, j, k, j)) {
                    Piece* ptr;
                    ptr = temp[k][j];
                    temp[k][j] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[k][j];
                        temp[k][j] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[k][j];
                    temp[k][j] = ptr;
                }
            }
            else if (arr[k][j] == nullptr) {
                if (CheckValidMoves(arr, i, j, k, j)) {
                    Piece* ptr;
                    ptr = temp[k][j];
                    temp[k][j] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[k][j];
                        temp[k][j] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[k][j];
                    temp[k][j] = ptr;
                }
            }
        }

        for (int k = i - 1; k >= 0; k--) {
            if (arr[k][j] != nullptr && arr[i][j]->getColor() != arr[k][j]->getColor()) {
                if (Capture(arr, i, j, k, j)) {
                    Piece* ptr;
                    ptr = temp[k][j];
                    temp[k][j] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[k][j];
                        temp[k][j] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[k][j];
                    temp[k][j] = ptr;
                }
            }
            else if (arr[k][j] == nullptr) {
                if (CheckValidMoves(arr, i, j, k, j)) {
                    Piece* ptr;
                    ptr = temp[k][j];
                    temp[k][j] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[k][j];
                        temp[k][j] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[k][j];
                    temp[k][j] = ptr;
                }
            }
        }

        return false;
    }

};

class King : public Piece
{

public:

    King()
    {
        color = '\0';
    }
    King(char ch)
    {
        color = ch;
    }
    virtual bool IsKing() {
        return true;
    }
    virtual void SetTexture()
    {
        if (color == 'b')
        {
            if (!Piecetxt.loadFromFile("pieces/p3.png"))
            {
            }
        }
        else
        {
            if (!Piecetxt.loadFromFile("pieces/p9.png"))
            {
            }
        }
        Chesspiece.setTexture(Piecetxt);
    }
    virtual bool CheckValidMoves(Piece* arr[8][8], int i, int j, int i1, int j1) {


        if ((i1 == i && (j1 == j + 1 || j1 == j - 1)) ||
            (j1 == j && (i1 == i + 1 || i1 == i - 1)) ||
            (i1 == i - 1 && (j1 == j + 1 || j1 == j - 1)) ||
            (i1 == i + 1 && (j1 == j + 1 || j1 == j - 1))) {
            return true;
        }
        return false;
    }
    virtual bool Capture(Piece* arr[8][8], int i, int j, int i1, int j1) {


        if ((this->getColor() == 'w' && arr[i1][j1]->getColor() == 'b') || (this->getColor() == 'b' && arr[i1][j1]->getColor() == 'w'))
        {
            if ((i1 == i && (j1 == j + 1 || j1 == j - 1)) ||
                (j1 == j && (i1 == i + 1 || i1 == i - 1)) ||
                (i1 == i - 1 && (j1 == j + 1 || j1 == j - 1)) ||
                (i1 == i + 1 && (j1 == j + 1 || j1 == j - 1))) {
                return true;
            }
        }
        return false;
    }
    virtual bool ValidMoveCheck(Piece* arr[8][8], int i, int j, int i1, int j1, int kx, int ky) {
        flag = false;
        if (this->CheckValidMoves(arr, i, j, i1, j1)) {
            arr[i1][j1] = arr[i][j];
            arr[i][j] = nullptr;

            if (!IsCheck(arr, i1, j1)) {
                flag = true;
            }
            else {

                arr[i][j] = arr[i1][j1];
                arr[i1][j1] = nullptr;
            }
        }
        else {
            return false;
        }

        return flag;
    }
    bool CaptureCheck(Piece* arr[8][8], int i, int j, int i1, int j1, int kx, int ky) {
        flag = false;
        if (arr[i1][j1]->IsKing()) {
            return false;
        }
        if (this->Capture(arr, i, j, i1, j1)) {
            Piece* ptr;
            ptr = arr[i1][j1];

            arr[i1][j1] = arr[i][j];
            arr[i][j] = nullptr;
            if (!IsCheck(arr, i1, j1)) {
                flag = true;
            }
            else {

                arr[i][j] = arr[i1][j1];
                arr[i1][j1] = ptr;

            }

        }
        else {
            return false;
        }

        return flag;
    }
    bool CaptureCheck_(Piece* arr[8][8], int i, int j, int i1, int j1, int kx, int ky) {

        Piece* temp[8][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                temp[i][j] = arr[i][j];
            }
        }

        flag = false;
        if (this->Capture(temp, i, j, i1, j1)) {
            Piece* ptr;
            ptr = temp[i1][j1];

            temp[i1][j1] = temp[i][j];
            temp[i][j] = nullptr;
            if (!IsCheck(temp, i1, j1)) {
                flag = true;
            }
            else {

                temp[i][j] = temp[i1][j1];
                temp[i1][j1] = ptr;

            }

        }
        else {
            return false;
        }

        return flag;
    }
    virtual bool ValidMoveCheck_(Piece* arr[8][8], int i, int j, int i1, int j1, int kx, int ky) {
        Piece* temp[8][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                temp[i][j] = arr[i][j];
            }
        }
        flag = false;
        if (this->CheckValidMoves(temp, i, j, i1, j1)) {
            temp[i1][j1] = temp[i][j];
            temp[i][j] = nullptr;

            if (!IsCheck(temp, i1, j1)) {
                flag = true;
            }
            else {

                temp[i][j] = temp[i1][j1];
                temp[i1][j1] = nullptr;
            }
        }
        else {
            return false;
        }

        return flag;
    }
};

class Queen : public Piece
{

public:

    Queen()
    {
        color = '\0';
    }
    Queen(char ch)
    {
        color = ch;
    }
    virtual void SetTexture()
    {
        if (color == 'b')
        {

            if (!Piecetxt.loadFromFile("pieces/p4.png"))
            {
            }
        }
        else
        {
            if (!Piecetxt.loadFromFile("pieces/p10.png"))
            {
            }
        }
        Chesspiece.setTexture(Piecetxt);
    }

    virtual bool CheckValidMoves(Piece* arr[8][8], int i, int j, int i1, int j1) {

        int start = 0, end = 0;

        if (i1 == i || j1 == j) {
            if (i1 == i) {

                if (j1 > j) {
                    start = j + 1;
                    end = j1;
                }
                else {
                    start = j1 + 1;
                    end = j;
                }
                for (int col = start; col < end; col++) {
                    if (arr[i][col] != nullptr) {
                        return false;
                    }
                }
            }
            else if (j1 == j) {
                if (i1 > i) {
                    start = i + 1;
                    end = i1;
                }
                else {
                    start = i1 + 1;
                    end = i;
                }
                for (int row = start; row < end; row++) {
                    if (arr[row][j] != nullptr) {
                        return false;
                    }
                }
            }
            return true;
        }

        else if ((i1 < i && j1 > j && (i - i1) == (j1 - j)) ||
            (i1 < i && j1 < j && (i - i1) == (j - j1)) ||
            (i1 > i && j1 > j && (i1 - i) == (j1 - j)) ||
            (i1 > i && j1 < j && (i1 - i) == (j - j1))) {

            if (i1 < i)
            {
                if (j1 > j)
                {
                    for (int k = j + 1, c = i - 1; k < j1; k++, c--)
                    {
                        if (arr[c][k] != nullptr)
                            return false;
                    }
                }
                else if (j1 < j)
                {
                    for (int c = i1 + 1, k = j1 + 1; c < i; c++, k++)
                    {
                        if (arr[c][k] != nullptr)
                            return false;
                    }
                }
            }
            else if (i1 > i)
            {
                if (j1 > j)
                {
                    for (int c = i + 1, k = j + 1; c < i1; c++, k++)
                    {
                        if (arr[c][k] != nullptr)
                            return false;
                    }
                }
                else if (j1 < j)
                {
                    for (int c = i + 1, k = j - 1; c < i1; c++, k--)
                    {
                        if (arr[c][k] != nullptr)
                            return false;
                    }
                }
            }
            return true;
        }
        return false;
    }

    virtual bool Capture(Piece* arr[8][8], int i, int j, int i1, int j1) {

        int start, end;

        if ((this->getColor() == 'w' && arr[i1][j1]->getColor() == 'b') || (this->getColor() == 'b' && arr[i1][j1]->getColor() == 'w'))
        {
            if (i1 == i || j1 == j) {
                if (i1 == i) {

                    if (j1 > j) {
                        start = j + 1;
                        end = j1;
                    }
                    else {
                        start = j1 + 1;
                        end = j;
                    }
                    for (int col = start; col < end; col++) {
                        if (arr[i][col] != nullptr) {
                            return false;
                        }
                    }
                }
                else if (j1 == j) {
                    if (i1 > i) {
                        start = i + 1;
                        end = i1;
                    }
                    else {
                        start = i1 + 1;
                        end = i;
                    }
                    for (int row = start; row < end; row++) {
                        if (arr[row][j] != nullptr) {
                            return false;
                        }
                    }
                }
                return true;
            }

            else if ((i1 < i && j1 > j && (i - i1) == (j1 - j)) ||
                (i1 < i && j1 < j && (i - i1) == (j - j1)) ||
                (i1 > i && j1 > j && (i1 - i) == (j1 - j)) ||
                (i1 > i && j1 < j && (i1 - i) == (j - j1))) {

                if (i1 < i)
                {
                    if (j1 > j)
                    {
                        for (int k = j + 1, c = i - 1; k < j1; k++, c--)
                        {
                            if (arr[c][k] != nullptr)
                                return false;
                        }
                    }
                    else if (j1 < j)
                    {
                        for (int c = i1 + 1, k = j1 + 1; c < i; c++, k++)
                        {
                            if (arr[c][k] != nullptr)
                                return false;
                        }
                    }
                }
                else if (i1 > i)
                {
                    if (j1 > j)
                    {
                        for (int c = i + 1, k = j + 1; c < i1; c++, k++)
                        {
                            if (arr[c][k] != nullptr)
                                return false;
                        }
                    }
                    else if (j1 < j)
                    {
                        for (int c = i + 1, k = j - 1; c < i1; c++, k--)
                        {
                            if (arr[c][k] != nullptr)
                                return false;
                        }
                    }
                }
                return true;
            }
        }
        return false;
    }
    virtual bool ValidMoveCheck(Piece* arr[8][8], int i, int j, int i1, int j1, int kx, int ky) {
        flag = false;
        if (this->CheckValidMoves(arr, i, j, i1, j1)) {
            arr[i1][j1] = arr[i][j];
            arr[i][j] = nullptr;
            if (!IsCheck(arr, kx, ky)) {
                flag = true;
            }
            else {
                arr[i][j] = arr[i1][j1];
                arr[i1][j1] = nullptr;
            }
        }
        else {
            return false;
        }
        return flag;
    }
    bool CaptureCheck(Piece* arr[8][8], int i, int j, int i1, int j1, int kx, int ky) {
        flag = false;

        if (arr[i1][j1]->IsKing()) {
            return false;
        }
        if (this->Capture(arr, i, j, i1, j1)) {
            Piece* ptr;
            ptr = arr[i1][j1];
            arr[i1][j1] = arr[i][j];
            arr[i][j] = nullptr;
            if (!IsCheck(arr, kx, ky)) {
                flag = true;
            }
            else {
                arr[i][j] = arr[i1][j1];
                arr[i1][j1] = ptr;

            }

        }
        else {
            return false;
        }

        return flag;
    }
    bool PossibleMoves(Piece* arr[8][8], int i, int j, int kx, int ky) {

        Piece* temp[8][8];
        for (int m = 0; m < 8; m++) {
            for (int n = 0; n < 8; n++) {
                temp[m][n] = arr[m][n];
            }
        }

        //Rook

        for (int k = j + 1; k < 8; k++) {
            if (arr[i][k] != nullptr && arr[i][j]->getColor() != arr[i][k]->getColor()) {
                if (Capture(arr, i, j, i, k)) {

                    Piece* ptr;
                    ptr = temp[i][k];
                    temp[i][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i][k];
                        temp[i][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i][k];
                    temp[i][k] = ptr;
                }
            }
            else if (arr[i][k] == nullptr) {
                if (CheckValidMoves(arr, i, j, i, k)) {

                    Piece* ptr;
                    ptr = temp[i][k];
                    temp[i][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i][k];
                        temp[i][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i][k];
                    temp[i][k] = ptr;
                }
            }
        }

        for (int k = j - 1; k >= 0; k--) {

            if (arr[i][k] != nullptr && arr[i][j]->getColor() != arr[i][k]->getColor()) {
                if (Capture(arr, i, j, i, k)) {
                    Piece* ptr;
                    ptr = temp[i][k];
                    temp[i][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i][k];
                        temp[i][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i][k];
                    temp[i][k] = ptr;
                }
            }
            else if (arr[i][k] == nullptr) {
                if (CheckValidMoves(arr, i, j, i, k)) {
                    Piece* ptr;
                    ptr = temp[i][k];
                    temp[i][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i][k];
                        temp[i][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i][k];
                    temp[i][k] = ptr;
                }
            }
        }

        for (int k = i + 1; k < 8; k++) {

            if (arr[k][j] != nullptr && arr[i][j]->getColor() != arr[k][j]->getColor()) {
                if (Capture(arr, i, j, k, j)) {
                    Piece* ptr;
                    ptr = temp[k][j];
                    temp[k][j] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[k][j];
                        temp[k][j] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[k][j];
                    temp[k][j] = ptr;
                }
            }
            else if (arr[k][j] == nullptr) {
                if (CheckValidMoves(arr, i, j, k, j)) {
                    Piece* ptr;
                    ptr = temp[k][j];
                    temp[k][j] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[k][j];
                        temp[k][j] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[k][j];
                    temp[k][j] = ptr;
                }
            }
        }

        for (int k = i - 1; k >= 0; k--) {
            if (arr[k][j] != nullptr && arr[i][j]->getColor() != arr[k][j]->getColor()) {
                if (Capture(arr, i, j, k, j)) {
                    Piece* ptr;
                    ptr = temp[k][j];
                    temp[k][j] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[k][j];
                        temp[k][j] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[k][j];
                    temp[k][j] = ptr;
                }
            }
            else if (arr[k][j] == nullptr) {
                if (CheckValidMoves(arr, i, j, k, j)) {
                    Piece* ptr;
                    ptr = temp[k][j];
                    temp[k][j] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[k][j];
                        temp[k][j] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[k][j];
                    temp[k][j] = ptr;
                }
            }
        }

        //BISHOP

        for (int l = i - 1, k = j + 1; k < 8 && l >= 0; l--, k++) {

            if (arr[l][k] != nullptr && arr[i][j]->getColor() != arr[l][k]->getColor()) {
                if (Capture(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
            else if (arr[l][k] == nullptr) {
                if (CheckValidMoves(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
        }

        for (int l = i - 1, k = j - 1; k >= 0 && l >= 0; k--, l--) {
            if (arr[l][k] != nullptr && arr[i][j]->getColor() != arr[l][k]->getColor()) {
                if (Capture(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
            else if (arr[l][k] == nullptr) {
                if (CheckValidMoves(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
        }

        for (int l = i + 1, k = j + 1; l < 8 && k < 8; k++, l++) {
            if (arr[l][k] != nullptr && arr[i][j]->getColor() != arr[l][k]->getColor()) {
                if (Capture(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
            else if (arr[l][k] == nullptr) {
                if (CheckValidMoves(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
        }


        for (int l = i + 1, k = j - 1; l < 8 && k >= 0; k--, l++) {
            if (arr[l][k] != nullptr && arr[i][j]->getColor() != arr[l][k]->getColor()) {
                if (Capture(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
            else if (arr[l][k] == nullptr) {
                if (CheckValidMoves(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
        }

        return false;

    }

};

class Bishop : public Piece
{

public:

    Bishop()
    {
        color = '\0';
    }
    Bishop(char ch)
    {
        color = ch;
    }
    virtual void SetTexture()
    {
        if (color == 'b')
        {

            if (!Piecetxt.loadFromFile("pieces/p5.png"))
            {
            }
        }
        else
        {
            if (!Piecetxt.loadFromFile("pieces/p11.png"))
            {
            }
        }
        Chesspiece.setTexture(Piecetxt);
    }
    virtual bool CheckValidMoves(Piece* arr[8][8], int i, int j, int i1, int j1) {

        if ((i1 < i && j1 > j && (i - i1) == (j1 - j)) ||
            (i1 < i && j1 < j && (i - i1) == (j - j1)) ||
            (i1 > i && j1 > j && (i1 - i) == (j1 - j)) ||
            (i1 > i && j1 < j && (i1 - i) == (j - j1)))
        {
            if (i1 < i)
            {
                if (j1 > j)
                {
                    for (int k = j + 1, c = i - 1; k < j1; k++, c--)
                    {
                        if (arr[c][k] != nullptr)
                            return false;
                    }
                }
                else if (j1 < j)
                {
                    for (int c = i1 + 1, k = j1 + 1; c < i; c++, k++)
                    {
                        if (arr[c][k] != nullptr)
                            return false;
                    }
                }
            }
            else if (i1 > i)
            {
                if (j1 > j)
                {
                    for (int c = i + 1, k = j + 1; c < i1; c++, k++)
                    {
                        if (arr[c][k] != nullptr)
                            return false;
                    }
                }
                else if (j1 < j)
                {
                    for (int c = i + 1, k = j - 1; c < i1; c++, k--)
                    {
                        if (arr[c][k] != nullptr)
                            return false;
                    }
                }
            }
            return true;
        }
        return false;
    }

    virtual bool Capture(Piece* arr[8][8], int i, int j, int i1, int j1) {


        if ((this->getColor() == 'w' && arr[i1][j1]->getColor() == 'b') || (this->getColor() == 'b' && arr[i1][j1]->getColor() == 'w'))
        {
            if ((i1 < i && j1 > j && (i - i1) == (j1 - j)) ||
                (i1 < i && j1 < j && (i - i1) == (j - j1)) ||
                (i1 > i && j1 > j && (i1 - i) == (j1 - j)) ||
                (i1 > i && j1 < j && (i1 - i) == (j - j1)))
            {
                if (i1 < i)
                {
                    if (j1 > j)
                    {
                        for (int k = j + 1, c = i - 1; k < j1; k++, c--)
                        {
                            if (arr[c][k] != nullptr)
                                return false;
                        }
                    }
                    else if (j1 < j)
                    {
                        for (int c = i1 + 1, k = j1 + 1; c < i; c++, k++)
                        {
                            if (arr[c][k] != nullptr)
                                return false;
                        }
                    }
                }
                else if (i1 > i)
                {
                    if (j1 > j)
                    {
                        for (int c = i + 1, k = j + 1; c < i1; c++, k++)
                        {
                            if (arr[c][k] != nullptr)
                                return false;
                        }
                    }
                    else if (j1 < j)
                    {
                        for (int c = i + 1, k = j - 1; c < i1; c++, k--)
                        {
                            if (arr[c][k] != nullptr)
                                return false;

                        }
                    }
                }
                return true;
            }
        }
        return false;
    }
    virtual bool ValidMoveCheck(Piece* arr[8][8], int i, int j, int i1, int j1, int kx, int ky) {
        flag = false;
        if (this->CheckValidMoves(arr, i, j, i1, j1)) {
            arr[i1][j1] = arr[i][j];
            arr[i][j] = nullptr;
            if (!IsCheck(arr, kx, ky)) {
                flag = true;
            }
            else {
                arr[i][j] = arr[i1][j1];
                arr[i1][j1] = nullptr;
            }
        }
        else {
            return false;
        }

        return flag;
    }
    bool CaptureCheck(Piece* arr[8][8], int i, int j, int i1, int j1, int kx, int ky) {
        flag = false;
        if (arr[i1][j1]->IsKing()) {
            return false;
        }
        if (this->Capture(arr, i, j, i1, j1)) {
            Piece* ptr;
            ptr = arr[i1][j1];
            arr[i1][j1] = arr[i][j];
            arr[i][j] = nullptr;
            if (!IsCheck(arr, kx, ky)) {
                flag = true;
            }
            else {
                arr[i][j] = arr[i1][j1];
                arr[i1][j1] = ptr;

            }

        }
        else {
            return false;
        }

        return flag;
    }
    bool PossibleMoves(Piece* arr[8][8], int i, int j, int kx, int ky) {

        Piece* temp[8][8];
        for (int m = 0; m < 8; m++) {
            for (int n = 0; n < 8; n++) {
                temp[m][n] = arr[m][n];
            }
        }

        for (int l = i - 1, k = j + 1; k < 8 && l >= 0; l--, k++) {

            if (arr[l][k] != nullptr && arr[i][j]->getColor() != arr[l][k]->getColor()) {
                if (Capture(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
            else if (arr[l][k] == nullptr) {
                if (CheckValidMoves(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
        }

        for (int l = i - 1, k = j - 1; k >= 0 && l >= 0; k--, l--) {
            if (arr[l][k] != nullptr && arr[i][j]->getColor() != arr[l][k]->getColor()) {
                if (Capture(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
            else if (arr[l][k] == nullptr) {
                if (CheckValidMoves(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
        }

        for (int l = i + 1, k = j + 1; l < 8 && k < 8; k++, l++) {
            if (arr[l][k] != nullptr && arr[i][j]->getColor() != arr[l][k]->getColor()) {
                if (Capture(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
            else if (arr[l][k] == nullptr) {
                if (CheckValidMoves(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
        }


        for (int l = i + 1, k = j - 1; l < 8 && k >= 0; k--, l++) {
            if (arr[l][k] != nullptr && arr[i][j]->getColor() != arr[l][k]->getColor()) {
                if (Capture(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
            else if (arr[l][k] == nullptr) {
                if (CheckValidMoves(arr, i, j, l, k)) {
                    Piece* ptr;
                    ptr = temp[l][k];
                    temp[l][k] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[l][k];
                        temp[l][k] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[l][k];
                    temp[l][k] = ptr;
                }
            }
        }

        return false;
    }
};

class Knight : public Piece
{

public:

    Knight()
    {
        color = '\0';
    }
    Knight(char ch)
    {
        color = ch;
    }
    virtual void SetTexture()
    {
        if (color == 'b')
        {

            if (!Piecetxt.loadFromFile("pieces/p6.png"))
            {
            }
        }
        else
        {
            if (!Piecetxt.loadFromFile("pieces/p12.png"))
            {
            }
        }
        Chesspiece.setTexture(Piecetxt);
    }
    virtual bool CheckValidMoves(Piece* arr[8][8], int i, int j, int i1, int j1) {

        if ((i1 == i + 2 && (j1 == j + 1 || j1 == j - 1)) ||
            (i1 == i + 1 && (j1 == j + 2 || j1 == j - 2)) ||
            (i1 == i - 1 && (j1 == j + 2 || j1 == j - 2)) ||
            (i1 == i - 2 && (j1 == j + 1 || j1 == j - 1))) {
            return true;
        }
        return false;
    }
    virtual bool Capture(Piece* arr[8][8], int i, int j, int i1, int j1) {

        if ((this->getColor() == 'w' && arr[i1][j1]->getColor() == 'b') || (this->getColor() == 'b' && arr[i1][j1]->getColor() == 'w')) {
            if ((i1 == i + 2 && (j1 == j + 1 || j1 == j - 1)) ||
                (i1 == i + 1 && (j1 == j + 2 || j1 == j - 2)) ||
                (i1 == i - 1 && (j1 == j + 2 || j1 == j - 2)) ||
                (i1 == i - 2 && (j1 == j + 1 || j1 == j - 1))) {
                return true;
            }
        }
        return false;
    }
    virtual bool ValidMoveCheck(Piece* arr[8][8], int i, int j, int i1, int j1, int kx, int ky) {
        flag = false;
        if (this->CheckValidMoves(arr, i, j, i1, j1)) {
            arr[i1][j1] = arr[i][j];
            arr[i][j] = nullptr;
            if (!IsCheck(arr, kx, ky)) {
                flag = true;
            }
            else {
                arr[i][j] = arr[i1][j1];
                arr[i1][j1] = nullptr;
            }
        }
        else {
            return false;
        }

        return flag;
    }
    bool CaptureCheck(Piece* arr[8][8], int i, int j, int i1, int j1, int kx, int ky) {
        flag = false;
        if (arr[i1][j1]->IsKing()) {
            return false;
        }
        if (this->Capture(arr, i, j, i1, j1)) {
            Piece* ptr;
            ptr = arr[i1][j1];
            arr[i1][j1] = arr[i][j];
            arr[i][j] = nullptr;
            if (!IsCheck(arr, kx, ky)) {
                flag = true;
            }
            else {
                arr[i][j] = arr[i1][j1];
                arr[i1][j1] = ptr;

            }

        }
        else {
            return false;
        }

        return flag;
    }
    bool PossibleMoves(Piece* arr[8][8], int i, int j, int kx, int ky) {

        Piece* temp[8][8];
        for (int m = 0; m < 8; m++) {
            for (int n = 0; n < 8; n++) {
                temp[m][n] = arr[m][n];
            }
        }

        if (i - 2 >= 0 && j + 1 < 8) {
            if (arr[i - 2][j + 1] != nullptr && arr[i][j]->getColor() != arr[i - 2][j + 1]->getColor()) {
                if (Capture(arr, i, j, i - 2, j + 1)) {
                    Piece* ptr;
                    ptr = temp[i - 2][j + 1];
                    temp[i - 2][j + 1] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i - 2][j + 1];
                        temp[i - 2][j + 1] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i - 2][j + 1];
                    temp[i - 2][j + 1] = ptr;
                }
            }
            else if (arr[i - 2][j + 1] == nullptr) {
                if (CheckValidMoves(arr, i, j, i - 2, j + 1)) {
                    Piece* ptr;
                    ptr = temp[i - 2][j + 1];
                    temp[i - 2][j + 1] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i - 2][j + 1];
                        temp[i - 2][j + 1] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i - 2][j + 1];
                    temp[i - 2][j + 1] = ptr;
                }
            }
        }

        if (i - 2 >= 0 && j - 1 >= 0) {
            if (arr[i - 2][j - 1] != nullptr && arr[i][j]->getColor() != arr[i - 2][j - 1]->getColor()) {
                if (Capture(arr, i, j, i - 2, j - 1)) {
                    Piece* ptr;
                    ptr = temp[i - 2][j - 1];
                    temp[i - 2][j - 1] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i - 2][j - 1];
                        temp[i - 2][j - 1] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i - 2][j - 1];
                    temp[i - 2][j - 1] = ptr;
                }
            }
            else if (arr[i - 2][j - 1] == nullptr) {
                if (CheckValidMoves(arr, i, j, i - 2, j - 1)) {
                    Piece* ptr;
                    ptr = temp[i - 2][j - 1];
                    temp[i - 2][j - 1] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i - 2][j - 1];
                        temp[i - 2][j - 1] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i - 2][j - 1];
                    temp[i - 2][j - 1] = ptr;
                }
            }
        }

        if (i - 1 >= 0 && j + 2 < 8) {
            if (arr[i - 1][j + 2] != nullptr && arr[i][j]->getColor() != arr[i - 1][j + 2]->getColor()) {
                if (Capture(arr, i, j, i - 1, j + 2)) {
                    Piece* ptr;
                    ptr = temp[i - 1][j + 2];
                    temp[i - 1][j + 2] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i - 1][j + 2];
                        temp[i - 1][j + 2] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i - 1][j + 2];
                    temp[i - 1][j + 2] = ptr;
                }
            }
            else if (arr[i - 1][j + 2] == nullptr) {
                if (CheckValidMoves(arr, i, j, i - 1, j + 2)) {
                    Piece* ptr;
                    ptr = temp[i - 1][j + 2];
                    temp[i - 1][j + 2] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i - 1][j + 2];
                        temp[i - 1][j + 2] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i - 1][j + 2];
                    temp[i - 1][j + 2] = ptr;
                }
            }
        }

        if (i - 1 >= 0 && j - 2 >= 0) {
            if (arr[i - 1][j - 2] != nullptr && arr[i][j]->getColor() != arr[i - 1][j - 2]->getColor()) {
                if (Capture(arr, i, j, i - 1, j - 2)) {
                    Piece* ptr;
                    ptr = temp[i - 1][j - 2];
                    temp[i - 1][j - 2] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i - 1][j - 2];
                        temp[i - 1][j - 2] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i - 1][j - 2];
                    temp[i - 1][j - 2] = ptr;
                }
            }
            else if (arr[i - 1][j - 2] == nullptr) {
                if (CheckValidMoves(arr, i, j, i - 1, j - 2)) {
                    Piece* ptr;
                    ptr = temp[i - 1][j - 2];
                    temp[i - 1][j - 2] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i - 1][j - 2];
                        temp[i - 1][j - 2] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i - 1][j - 2];
                    temp[i - 1][j - 2] = ptr;
                }
            }
        }

        if (i + 1 < 8 && j + 2 < 8) {
            if (arr[i + 1][j + 2] != nullptr && arr[i][j]->getColor() != arr[i + 1][j + 2]->getColor()) {
                if (Capture(arr, i, j, i + 1, j + 2)) {
                    Piece* ptr;
                    ptr = temp[i + 1][j + 2];
                    temp[i + 1][j + 2] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i + 1][j + 2];
                        temp[i + 1][j + 2] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i + 1][j + 2];
                    temp[i + 1][j + 2] = ptr;
                }
            }
            else if (arr[i + 1][j + 2] == nullptr) {
                if (CheckValidMoves(arr, i, j, i + 1, j + 2)) {
                    Piece* ptr;
                    ptr = temp[i + 1][j + 2];
                    temp[i + 1][j + 2] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i + 1][j + 2];
                        temp[i + 1][j + 2] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i + 1][j + 2];
                    temp[i + 1][j + 2] = ptr;
                }
            }
        }

        if (i + 1 < 8 && j - 2 >= 0) {
            if (arr[i + 1][j - 2] != nullptr && arr[i][j]->getColor() != arr[i + 1][j - 2]->getColor()) {
                if (Capture(arr, i, j, i + 1, j - 2)) {
                    Piece* ptr;
                    ptr = temp[i + 1][j - 2];
                    temp[i + 1][j - 2] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i + 1][j - 2];
                        temp[i + 1][j - 2] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i + 1][j - 2];
                    temp[i + 1][j - 2] = ptr;
                }
            }
            else if (arr[i + 1][j - 2] == nullptr) {
                if (CheckValidMoves(arr, i, j, i + 1, j - 2)) {
                    Piece* ptr;
                    ptr = temp[i + 1][j - 2];
                    temp[i + 1][j - 2] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i + 1][j - 2];
                        temp[i + 1][j - 2] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i + 1][j - 2];
                    temp[i + 1][j - 2] = ptr;
                }
            }
        }


        if (i + 2 < 8 && j + 1 < 8) {
            if (arr[i + 2][j + 1] != nullptr && arr[i][j]->getColor() != arr[i + 2][j + 1]->getColor()) {
                if (Capture(arr, i, j, i + 2, j + 1)) {
                    Piece* ptr;
                    ptr = temp[i + 2][j + 1];
                    temp[i + 2][j + 1] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i + 2][j + 1];
                        temp[i + 2][j + 1] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i + 2][j + 1];
                    temp[i + 2][j + 1] = ptr;
                }
            }
            else if (arr[i + 2][j + 1] == nullptr) {
                if (CheckValidMoves(arr, i, j, i + 2, j + 1)) {
                    Piece* ptr;
                    ptr = temp[i + 2][j + 1];
                    temp[i + 2][j + 1] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i + 2][j + 1];
                        temp[i + 2][j + 1] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i + 2][j + 1];
                    temp[i + 2][j + 1] = ptr;
                }
            }
        }

        if (i + 2 < 8 && j - 1 >= 0) {
            if (arr[i + 2][j - 1] != nullptr && arr[i][j]->getColor() != arr[i + 2][j - 1]->getColor()) {
                if (Capture(arr, i, j, i + 2, j - 1)) {
                    Piece* ptr;
                    ptr = temp[i + 2][j - 1];
                    temp[i + 2][j - 1] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i + 2][j - 1];
                        temp[i + 2][j - 1] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i + 2][j - 1];
                    temp[i + 2][j - 1] = ptr;
                }
            }
            else if (arr[i + 2][j - 1] == nullptr) {
                if (CheckValidMoves(arr, i, j, i + 2, j - 1)) {
                    Piece* ptr;
                    ptr = temp[i + 2][j - 1];
                    temp[i + 2][j - 1] = temp[i][j];
                    temp[i][j] = nullptr;
                    if (!IsCheck(temp, kx, ky)) {
                        temp[i][j] = temp[i + 2][j - 1];
                        temp[i + 2][j - 1] = ptr;
                        return true;
                    }
                    temp[i][j] = temp[i + 2][j - 1];
                    temp[i + 2][j - 1] = ptr;
                }
            }
        }

        return false;
    }
};


void GetKingPos(Piece* arr[8][8], int& kx, int& ky, char color) {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (arr[i][j] != nullptr)
                if (arr[i][j] != nullptr && arr[i][j]->getColor() == color)
                    if (arr[i][j]->IsKing()) {
                        kx = i;
                        ky = j;
                        return;
                    }
        }
    }
}

bool IsCheck(Piece* arr[8][8], int kx, int ky) {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {


            if (arr[i][j] != nullptr && arr[kx][ky] != nullptr && arr[i][j]->getColor() != arr[kx][ky]->getColor()) {
                if (arr[i][j]->Capture(arr, i, j, kx, ky)) {
                    //cout << "King In check" << endl;
                    return true;

                }
            }
        }
    }
    // cout << "King Not In check" << endl;
    return false;
}

bool PossibleMovesCheck(Piece* arr[8][8], int kx, int ky) {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (arr[i][j] != nullptr)
                if (arr[i][j]->getColor() == arr[kx][ky]->getColor())
                    if (arr[i][j]->PossibleMoves(arr, i, j, kx, ky)) {
                        return true;
                    }
        }
    }
    return false;
}

bool IsCheckmate(Piece* arr[8][8], int i, int j) {

    if (!IsCheck(arr, i, j)) {
        return false;
    }

    if (PossibleMovesCheck(arr, i, j)) {
        return false;
    }

    if (j + 1 >= 0 && j + 1 < 8 && i - 1 >= 0 && i - 1 < 8) {
        if (arr[i - 1][j + 1] == nullptr) {
            if (arr[i][j]->ValidMoveCheck_(arr, i, j, i - 1, j + 1, i, j)) {
                return false;
            }
        }
        else {

            if (arr[i][j]->CaptureCheck_(arr, i, j, i - 1, j + 1, i, j)) {
                return false;
            }
        }
    }

    if (j >= 0 && j < 8 && i - 1 >= 0 && i - 1 < 8) {
        if (arr[i - 1][j] == nullptr) {
            if (arr[i][j]->ValidMoveCheck_(arr, i, j, i - 1, j, i, j)) {
                return false;
            }
        }

        else {

            if (arr[i][j]->CaptureCheck_(arr, i, j, i - 1, j, i, j)) {
                return false;
            }
        }
    }

    if (j - 1 >= 0 && j - 1 < 8 && i - 1 >= 0 && i - 1 < 8) {
        if (arr[i - 1][j - 1] == nullptr) {
            if (arr[i][j]->ValidMoveCheck_(arr, i, j, i - 1, j - 1, i, j)) {
                return false;
            }
        }
        else {

            if (arr[i][j]->CaptureCheck_(arr, i, j, i - 1, j - 1, i, j)) {
                return false;
            }
        }
    }

    if (j - 1 >= 0 && j - 1 < 8 && i >= 0 && i < 8) {
        if (arr[i][j - 1] == nullptr) {
            if (arr[i][j]->ValidMoveCheck_(arr, i, j, i, j - 1, i, j)) {
                return false;
            }
        }
        else {
            if (arr[i][j]->CaptureCheck_(arr, i, j, i, j - 1, i, j)) {
                return false;
            }
        }
    }
    
    if (j - 1 >= 0 && j - 1 < 8 && i + 1 >= 0 && i + 1 < 8)
        if (arr[i + 1][j - 1] == nullptr) {
            if (arr[i][j]->ValidMoveCheck_(arr, i, j, i + 1, j - 1, i, j)) {
                return false;
            }
        }
        else {
            if (arr[i][j]->CaptureCheck_(arr, i, j, i + 1, j - 1, i, j)) {
                return false;
            }
        }

    if (j >= 0 && j < 8 && i + 1 >= 0 && i + 1 < 8)
    {
        if (arr[i + 1][j] == nullptr) {
            if (arr[i][j]->ValidMoveCheck_(arr, i, j, i + 1, j, i, j)) {
                return false;
            }
        }
        else {
            if (arr[i][j]->CaptureCheck_(arr, i, j, i + 1, j, i, j)) {
                return false;
            }
        }
    }

    if (j + 1 >= 0 && j + 1 < 8 && i + 1 >= 0 && i + 1 < 8) {

        if (arr[i + 1][j + 1] == nullptr) {
            if (arr[i][j]->ValidMoveCheck_(arr, i, j, i + 1, j + 1, i, j)) {
                return false;
            }
        }
        else {
            if (arr[i][j]->CaptureCheck_(arr, i, j, i + 1, j + 1, i, j)) {
                return false;
            }
        }
    }
    return true;
}

bool IsStalemate(Piece* arr[8][8], int i, int j) {

    if (IsCheck(arr, i, j)) {
        return false;
    }

    if (PossibleMovesCheck(arr, i, j)) {
        return false;
    }

    if (j + 1 >= 0 && j + 1 < 8 && i - 1 >= 0 && i - 1 < 8) {
        if (arr[i - 1][j + 1] == nullptr) {
            if (arr[i][j]->ValidMoveCheck_(arr, i, j, i - 1, j + 1, i, j)) {
                return false;
            }
        }
        else {

            if (arr[i][j]->CaptureCheck_(arr, i, j, i - 1, j + 1, i, j)) {
                return false;
            }
        }
    }

    if (j >= 0 && j < 8 && i - 1 >= 0 && i - 1 < 8) {
        if (arr[i - 1][j] == nullptr) {
            if (arr[i][j]->ValidMoveCheck_(arr, i, j, i - 1, j, i, j)) {
                return false;
            }
        }

        else {

            if (arr[i][j]->CaptureCheck_(arr, i, j, i - 1, j, i, j)) {
                return false;
            }
        }
    }

    if (j - 1 >= 0 && j - 1 < 8 && i - 1 >= 0 && i - 1 < 8) {
        if (arr[i - 1][j - 1] == nullptr) {
            if (arr[i][j]->ValidMoveCheck_(arr, i, j, i - 1, j - 1, i, j)) {
                return false;
            }
        }
        else {

            if (arr[i][j]->CaptureCheck_(arr, i, j, i - 1, j - 1, i, j)) {
                return false;
            }
        }
    }

    if (j - 1 >= 0 && j - 1 < 8 && i >= 0 && i < 8) {
        if (arr[i][j - 1] == nullptr) {
            if (arr[i][j]->ValidMoveCheck_(arr, i, j, i, j - 1, i, j)) {
                return false;
            }
        }
        else {
            if (arr[i][j]->CaptureCheck_(arr, i, j, i, j - 1, i, j)) {
                return false;
            }
        }
    }

    if (j - 1 >= 0 && j - 1 < 8 && i + 1 >= 0 && i + 1 < 8)
        if (arr[i + 1][j - 1] == nullptr) {
            if (arr[i][j]->ValidMoveCheck_(arr, i, j, i + 1, j - 1, i, j)) {
                return false;
            }
        }
        else {
            if (arr[i][j]->CaptureCheck_(arr, i, j, i + 1, j - 1, i, j)) {
                return false;
            }
        }

    if (j >= 0 && j < 8 && i + 1 >= 0 && i + 1 < 8)
    {
        if (arr[i + 1][j] == nullptr) {
            if (arr[i][j]->ValidMoveCheck_(arr, i, j, i + 1, j, i, j)) {
                return false;
            }
        }
        else {
            if (arr[i][j]->CaptureCheck_(arr, i, j, i + 1, j, i, j)) {
                return false;
            }
        }
    }

    if (j + 1 >= 0 && j + 1 < 8 && i + 1 >= 0 && i + 1 < 8) {

        if (arr[i + 1][j + 1] == nullptr) {
            if (arr[i][j]->ValidMoveCheck_(arr, i, j, i + 1, j + 1, i, j)) {
                return false;
            }
        }
        else {
            if (arr[i][j]->CaptureCheck_(arr, i, j, i + 1, j + 1, i, j)) {
                return false;
            }
        }
    }

    return true;
}

//////GAME WINDOW///////
void GameWindow()
{

    RenderWindow Window(VideoMode(1400, 934), "Game Window");
    Chessboard* Board = new Chessboard;

    Piece* arr[8][8] = {};

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {

            if (i == 0 || i == 7)
            {
                if (j == 0 || j == 7)
                {
                    if (i == 0)
                    {
                        arr[i][j] = new Rook('w');
                    }
                    else
                    {
                        arr[i][j] = new Rook('b');
                    }
                }
                else if (j == 1 || j == 6)
                {
                    if (i == 0)
                    {
                        arr[i][j] = new Knight('w');
                    }
                    else
                    {
                        arr[i][j] = new Knight('b');
                    }
                }
                else if (j == 2 || j == 5)
                {
                    if (i == 0)
                    {
                        arr[i][j] = new Bishop('w');
                    }
                    else
                    {
                        arr[i][j] = new Bishop('b');
                    }
                }
                else if (j == 3)
                {
                    if (i == 0)
                    {
                        arr[i][j] = new Queen('w');
                    }
                    else
                    {
                        arr[i][j] = new Queen('b');
                    }
                }
                else if (j == 4)
                {
                    if (i == 0)
                    {
                        arr[i][j] = new King('w');
                    }
                    else
                    {
                        arr[i][j] = new King('b');
                    }
                }
            }
            if (i == 1)
            {
                arr[i][j] = new Pawns('w');
            }
            else if (i == 6)
            {
                arr[i][j] = new Pawns('b');
            }
            if (arr[i][j] != nullptr)
            {
                arr[i][j]->SetTexture();
                arr[i][j]->Chesspiece.setPosition(10 + (95 * j), 150 + (95 * i));
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Green Dot

    RectangleShape Dot1;
    Dot1.setSize(Vector2f(20, 20));

    Texture DotTexture1;
    if (!DotTexture1.loadFromFile("Backgrounds/Dot.png"))
    {
    }
    Dot1.setTexture(&DotTexture1);
    Dot1.setPosition(820, 370);

    //

    RectangleShape Dot;
    Dot.setSize(Vector2f(20, 20));

    Texture DotTexture;
    if (!DotTexture.loadFromFile("Backgrounds/Dot.png"))
    {
    }
    Dot.setTexture(&DotTexture);
    Dot.setPosition(820, 670);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //GRAY BG

    RectangleShape Gray;
    Gray.setSize(Vector2f(450, 360));

    Texture Graytxt;
    if (!Graytxt.loadFromFile("Backgrounds/Gray.jpg"))
    {
    }
    Gray.setTexture(&Graytxt);
    Gray.setPosition(770, 350);
   

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // FONT

    Font font;
    if (!font.loadFromFile("Fonts/arial.ttf")) {}


    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TEXT 

    //PLAYER 1
    Text Player1;
    Player1.setFont(font);
    Player1.setString("Player 1");
    Player1.setCharacterSize(40);
    Player1.setPosition(850, 350);
    Player1.setFillColor(Color::White);

    //PLAYER 2
    Text Player2;
    Player2.setFont(font);
    Player2.setString("Player 2");
    Player2.setCharacterSize(40);
    Player2.setPosition(850, 650);
    Player2.setFillColor(Color::White);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////  CHECKMATES AND STALEMATES

    Color color(128,128,128);


    Text WC;
    WC.setFont(font);
    WC.setString("Black Wins by CheckMate");
    WC.setCharacterSize(30);
    WC.setPosition(820, 500);
    WC.setFillColor(color);

    Text BC;
    BC.setFont(font);
    BC.setString("White Wins by CheckMate");
    BC.setCharacterSize(30);
    BC.setPosition(820, 500);
    BC.setFillColor(color);

    Text SM;
    SM.setFont(font);
    SM.setString("1/2 - 1/2 (Draw)");
    SM.setCharacterSize(30);
    SM.setPosition(820, 500);
    SM.setFillColor(color);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TIMER


     
    // TIME 1
    Clock timer1;
    Time elapsedTime1;
    Time timeLimit1 = seconds(600);


    Text time1;
    time1.setFont(font);
    time1.setCharacterSize(40);
    time1.setPosition(840, 300);
    time1.setFillColor(color);

    // TIME 2
    Clock timer2;
    Time elapsedTime2;
    Time timeLimit2 = seconds(600);
    
    Text time2;
    time2.setFont(font);
    time2.setCharacterSize(40);
    time2.setPosition(840, 710);
    time2.setFillColor(color);

    int i = 0, j = 0;
    int i1 = 0, j1 = 0;
    int kx, ky;
    bool pieceSelected = false;
    bool flag = true;
    int wky, wkx, bky, bkx = 0;
    bool playerTurn = true;

    char ch = '\0';

    while (Window.isOpen())
    {
        Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {

                Window.close();
            }

            GetKingPos(arr, wkx, wky, 'w');
            GetKingPos(arr, bkx, bky, 'b');

            //  cout << wkx << " " << wky << " " << bkx << " " << bky << " " << endl;

            if (IsCheckmate(arr, wkx, wky))
            {
                ch = 'w';
            }
            else if (IsCheckmate(arr, bkx, bky))
            {
                ch = 'b';
            }
            else if (IsStalemate(arr, bkx, bky))
            {
                ch = 's';
            }
            else if (IsStalemate(arr, wkx, wky))
            {
                ch = 's';
            }

        
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                if (!pieceSelected)
                {
                   
                    i = (Mouse::getPosition(Window).y - 150) / 95;
                    j = (Mouse::getPosition(Window).x - 10) / 95;

                    if (j >= 0 && j < 8 && i >= 0 && i < 8 && arr[i][j] != nullptr)
                    {

                        pieceSelected = true;
                        if (playerTurn && arr[i][j]->getColor() != 'w' && arr[i][j] != nullptr)
                        {       
                            pieceSelected = false;
                        }
                        if (!playerTurn && arr[i][j]->getColor() != 'b' && arr[i][j] != nullptr)
                        {
                            pieceSelected = false;
                        }
                    }

                    if (arr[i][j] != nullptr)
                        GetKingPos(arr, kx, ky, arr[i][j]->getColor());

                }
                else
                {

                    i1 = (Mouse::getPosition(Window).y - 150) / 95;
                    j1 = (Mouse::getPosition(Window).x - 10) / 95;

                    if (j1 >= 0 && j1 < 8 && i1 >= 0 && i1 < 8)
                    {
                        if (arr[i1][j1] == nullptr) {
                            if (arr[i][j]->ValidMoveCheck(arr, i, j, i1, j1, kx, ky)) {

                                arr[i1][j1]->Chesspiece.setPosition(10 + (95 * j1), 150 + (95 * i1));
                                playerTurn = !playerTurn;
                            }

                            pieceSelected = false;

                        }
                        else if (arr[i1][j1] != nullptr) {
                            if (arr[i][j]->CaptureCheck(arr, i, j, i1, j1, kx, ky)) {
                                arr[i1][j1]->Chesspiece.setPosition(10 + (95 * j1), 150 + (95 * i1));
                                playerTurn = !playerTurn;
                            }
                            pieceSelected = false;

                        }
                    }
                }
            }
        }

        for (int c = 0; c < 8; c += 7)
        {
            for (int k = 0; k < 8; k++)
            {
                if (arr[c][k] != nullptr && arr[c][k]->isPawn())
                {
                    int pawn = PawnPromotion();
                    cout << pawn << endl;
                    switch (pawn)
                    {
                    case 1:
                        if (arr[c][k]->getColor() == 'w')
                        {
                            arr[c][k] = new Queen('w');
                        }
                        else if (arr[c][k]->getColor() == 'b')
                        {
                            arr[c][k] = new Queen('b');
                        }
                        break;
                    case 2:
                        if (arr[c][k]->getColor() == 'w')
                        {
                            arr[c][k] = new Knight('w');
                        }
                        else if (arr[c][k]->getColor() == 'b')
                        {
                            arr[c][k] = new Knight('b');
                        }
                        break;
                    case 3:
                        if (arr[c][k]->getColor() == 'w')
                        {
                            arr[c][k] = new Rook('w');
                        }
                        else if (arr[c][k]->getColor() == 'b')
                        {
                            arr[c][k] = new Rook('b');
                        }
                        break;
                    case 4:
                        if (arr[c][k]->getColor() == 'w')
                        {
                            arr[c][k] = new Bishop('w');
                        }
                        else if (arr[c][k]->getColor() == 'b')
                        {
                            arr[c][k] = new Bishop('b');
                        }
                        break;
                    }
                   
                        arr[c][k]->SetTexture();
                        arr[c][k]->Chesspiece.setPosition(10 + (95 * k), 150 + (95 * c));
                    
                }
            }
        }
        Board->DrawBg(Window);

        // Draw chess pieces
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (arr[i][j] != nullptr)
                {
                    Window.draw(arr[i][j]->Chesspiece);
                }
            }
        }

        if (playerTurn) {
            elapsedTime1 = timer1.getElapsedTime();
            int timeLeft1 = 600 - elapsedTime1.asSeconds();
            time1.setString(to_string(timeLeft1));
        }
        else if (!playerTurn) {
            elapsedTime2 = timer2.getElapsedTime();
            int timeLeft2 = 600 - elapsedTime2.asSeconds();
            time2.setString(to_string(timeLeft2));
        }

        Window.draw(Gray);
        Window.draw(Player1);
        Window.draw(Player2);
        Window.draw(Dot1);
        Window.draw(Dot);
        Window.draw(time1);
        Window.draw(time2);
        switch (ch) {
        case 'w':
            Window.draw(WC);
            break;

        case 'b':
            Window.draw(BC);
            break;

        case 's':
            Window.draw(SM);
            break;     
        }
        Window.display();
    }

    delete Board;
}

int PawnPromotion() {
    RenderWindow window(VideoMode(400, 500), "Game Menu");
    window.setPosition(sf::Vector2i(1200, 300));

    // Background
    Texture Bg;
    if (!Bg.loadFromFile("Backgrounds/menu.jpg")) {
    }
    Sprite BgSprite;
    BgSprite.setTexture(Bg);

    // Queen
    Texture QTxt;
    if (!QTxt.loadFromFile("images/p10.png")) {
    }
    Sprite QSpr;
    QSpr.setTexture(QTxt);
    QSpr.setPosition(80, 20);

    // Knight
    Texture KTxt;
    if (!KTxt.loadFromFile("images/p12.png")) {
    }
    Sprite KSpr;
    KSpr.setTexture(KTxt);
    KSpr.setPosition(260, 20);

    // Rook
    Texture RTxt;
    if (!RTxt.loadFromFile("images/p8.png")) {
    }
    Sprite RSpr;
    RSpr.setTexture(RTxt);
    RSpr.setPosition(80, 200);

    // Bishop
    Texture BTxt;
    if (!BTxt.loadFromFile("images/p11.png")) {
    }
    Sprite BSpr;
    BSpr.setTexture(BTxt);
    BSpr.setPosition(260, 200);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(window);

                // Checking if the mouse is within the bounds of the sprites
                if (mousePos.x >= 80 && mousePos.x <= 180 && mousePos.y >= 20 && mousePos.y <= 120) {
                    window.close();
                    return 1; // Queen
                }
                else if (mousePos.x >= 260 && mousePos.x <= 360 && mousePos.y >= 20 && mousePos.y <= 120) {
                    window.close();
                    return 2; // Knight
                }
                else if (mousePos.x >= 80 && mousePos.x <= 180 && mousePos.y >= 200 && mousePos.y <= 300) {
                    window.close();
                    return 3; // Rook
                }
                else if (mousePos.x >= 260 && mousePos.x <= 360 && mousePos.y >= 200 && mousePos.y <= 300) {
                    window.close();
                    return 4; // Bishop
                }
            }
        }

        window.clear();
        window.draw(BgSprite);
        window.draw(QSpr);
        window.draw(KSpr);
        window.draw(RSpr);
        window.draw(BSpr);
        window.display();
    }

    return 0;
}



//////MENU WINDOW/////
static void GameMenu()
{

    RenderWindow window(VideoMode(1350, 899), "Game Menu");

    // Background

    Texture Bg;
    if (!Bg.loadFromFile("Backgrounds/menu.jpg"))
    {
    }
    Sprite BgSprite;

    BgSprite.setTexture(Bg);

    // PLAY

    RectangleShape play;
    play.setSize(Vector2f(300, 200));

    Texture playTexture;
    if (!playTexture.loadFromFile("Backgrounds/playy.png"))
    {
    }
    play.setTexture(&playTexture);
    play.setPosition(550, 50);

    // QUIT
    RectangleShape quit;
    quit.setSize(Vector2f(300, 200));

    Texture quitTexture;
    if (!quitTexture.loadFromFile("Backgrounds/quitt.png"))
    {
    }
    quit.setTexture(&quitTexture);
    quit.setPosition(550, 250);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (mousePos.x >= 550 && mousePos.x <= 850 && mousePos.y >= 50 && mousePos.y <= 250)
                {
                    window.close();
                    GameWindow();
                }

                if (mousePos.x >= 550 && mousePos.x <= 850 && mousePos.y >= 250 && mousePos.y <= 450)
                {
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(BgSprite);
        window.draw(play);
        window.draw(quit);

        window.display();
    }
}

int main()
{
    srand(time(0));
    // create the window
    RenderWindow window(VideoMode(1350, 899), "Opening Window");

    // Background

    Texture Bg;
    if (!Bg.loadFromFile("Backgrounds/owbg.jpg"))
    {
    }

    Sprite BgSprite;
    BgSprite.setTexture(Bg);

    // Timer

    Clock timer;
    Time elapsedTime;
    Time timeLimit = seconds(5);

    // Font

    Font Opwfont;
    if (!Opwfont.loadFromFile("Fonts/OpeningW.ttf"))
    {
    }
    // chess mark
    RectangleShape chess;
    chess.setSize(Vector2f(350, 300));

    Texture chessTexture;
    if (!chessTexture.loadFromFile("Backgrounds/chessmark.png"))
    {
    }
    chess.setTexture(&chessTexture);
    chess.setPosition(900, 300);

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::Closed)
                window.close();
        }
        // timer
        elapsedTime = timer.getElapsedTime();
        if (elapsedTime >= timeLimit)
        {
            window.close();
            GameMenu();

        }
        window.draw(BgSprite);
        window.draw(chess);

        window.display();
    }

    return 0;
}