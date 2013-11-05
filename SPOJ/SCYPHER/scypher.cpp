//============================================================================
// Name        : scypher.cpp
// Author      : Michal Marcinkowski
// Description : www.spoj.com/problems/SCYPHER
//============================================================================

#include <cstdio>
#include <cstring>
#include <cstdlib>


using namespace std;

bool graph[26][26];

bool duplicates[26];
int paths[26];

int graphSize;

int getStartPoint(int from) {
    bool found;
    for (int i = from; i < graphSize; i++) {
        found = true;
        for (int j = 0; j < graphSize; j++) {
            if (graph[j][i] == true) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;
        }
    }
    return -1;
}

void DFS(int startPoint) {
    int path = paths[startPoint] + 1;
    for(int i = 0; i < graphSize; i++) {
        if (graph[startPoint][i] == true) {
            if (path > paths[i]) {
                paths[i] = path;
                DFS(i);
            }
        }
    }
}

void DFS2(int startPoint) {
    int path = paths[startPoint] + 1;
    for(int i = 0; i < graphSize; i++) {
        if (graph[startPoint][i] == true) {
            if (paths[i] != 0) {
                path = paths[i] + 1;
                paths[i] = path;
                DFS(i);
                break;
            }
        }
    }
}

int main() {
    int numberOfCases, numberOfWords, i, lastWordLength, wordLength, startPoint;
    bool ok;
    char buffer[2][100000];
    char* lastWord = &buffer[0][0];
    char* word = &buffer[1][0];
    scanf("%d", &numberOfCases);
    while(numberOfCases--) {
        ok = true;
        memset(duplicates, 0, sizeof(duplicates));
        memset(paths, -1, sizeof(paths));
        for (int i = 0; i < 26; i++) {
            memset(graph[i], 0, sizeof(graph[i]));
        }

        scanf("%d %d", &graphSize, &numberOfWords);
        //get new line char
        gets(lastWord);
        //get word
        gets(lastWord);
        numberOfWords--;
        while(numberOfWords--) {
            gets(word);
            lastWordLength = strlen(lastWord);
            wordLength = strlen(word);
            for(i = 0; (i < lastWordLength) && (i < wordLength); i++) {
                if (lastWord[i] != word[i]) {
                    graph[lastWord[i] - 'a'][word[i] - 'a'] = true;
                    break;
                }
            }
            strcpy(lastWord, word);
        }
        gets(word);

        int c = 1;
        startPoint = getStartPoint(0);
        paths[startPoint] = 0;
        DFS(startPoint);
        while((startPoint = getStartPoint(startPoint + 1)) != -1) {
            paths[startPoint] = 0;
            DFS2(startPoint);
        }

        for (i = 0; i < graphSize; i++) {
            if (duplicates[paths[i]]) {
                    ok = false;
                break;
            }
            duplicates[paths[i]] = true;
        }
        if (ok) {
            for (i = 0; i < strlen(word); i++) {
                    if ((word[i] < 'a') || (word[i] > 'z')) {
                        continue;
                    }
                if (paths[word[i] - 'a'] == -1) {
                    ok = false;
                    break;
                }
                word[i] = paths[word[i] - 'a'] + 'a';
            }
        }
        if (ok) {
            printf("%s\n", word);
        } else {
            printf("Message cannot be decrypted.\n");
        }
    }
}

