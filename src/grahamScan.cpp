#include "include/grahamScan.hpp"

// Um ​​ponto global é necessário para classificar pontos com referência
// até o primeiro ponto usado na função de comparação de qsort()
Point p0;

// Função para encontrar próximo ao topo de uma pilha
Point nextToTop(stack<Point> &S){
	Point p = S.top();
	S.pop();
	Point res = S.top();
	S.push(p);
	return res;
}

// Função para trocar dois pontos
void swap(Point &p1, Point &p2){
	Point temp = p1;
	p1 = p2;
	p2 = temp;
}

// Função que retorna o quadrado da distância entre p1 e p2
int distSquared(Point p1, Point p2){
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

// Para encontrar a orientação do trio ordenado (p, q, r).
//A função retorna os seguintes valores
// 0 --> p, q e r são colineares
// 1 --> Sentido horário
// 2 --> Sentido anti-horário
int orientation(Point p, Point q, Point r){
	int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;
	return (val > 0)? 1: 2;
}

// Função usada pela função da biblioteca qsort() para classificar uma matriz de 
// pontos em relação ao primeiro ponto
int compare(const void *vp1, const void *vp2){
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    // Encontrar a orientação
    int o = orientation(p0, *p1, *p2);
    if (o == 0){
        return (distSquared(p0, *p2) >= distSquared(p0, *p1))? -1 : 1;
    } 

    return (o == 2)? -1: 1;
}

// Imprime o envoltório convexo de um conjunto de n pontos
void convexHull(Point points[], int n){
    int ymin = points[0].y, min = 0;

    // Encontra o ponto mais baixo
    for (int i = 1; i < n; i++){
        int y = points[i].y;

        // Escolhe o ponto mais baixo ou escolhe o ponto mais à extrema 
        // esquerda em caso de empate
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)){
            ymin = points[i].y, min = i;
        }
    }

    // Coloca o ponto mais baixo na primeira posição
    swap(points[0], points[min]);

    // Organiza n-1 pontos em relação ao primeiro ponto.
    // Um ​​ponto p1 vem antes de p2 na saída ordenada se p2 tiver 
    // ângulo polar maior (no sentido anti-horário) que p1
    p0 = points[0];
    qsort(&points[1], n-1, sizeof(Point), compare);

    // Se dois ou mais pontos formam o mesmo ângulo com p0, remove todos, 
    // exceto aquele que está mais distante de p0
    // Na classificação acima, o critério foi para manter 
    // o ponto mais distante no final quando mais de um ponto tem o mesmo ângulo.
    int m = 1;
    for (int i=1; i<n; i++){
        // Continua removendo i enquanto o ângulo de i e i+1 for o mesmo em relação a p0
        while(i < n-1 && orientation(p0, points[i], points[i+1]) == 0){
            i++;
        }

        points[m] = points[i];
        m++;
    }

    // Se o array de pontos modificado tiver menos ou for igual a 3 pontos, 
    // envoltório convexo não é possível
    if(m <= 3){
        cout << VERMELHO << "ENVOLTÓRIO CONVEXO NÃO É POSSÍVEL! :(" << RESET << endl;
        return;
    }

    // Cria uma pilha vazia e empurra os três primeiros pontos.
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // Processa n-3 pontos restantes
    for (int i = 3; i < m; i++){
        // Continua removendo o topo enquanto o ângulo formado por
        // pontos próximo ao topo (next-to-stop), top e points[i] faz
        // uma curva não à esquerda
        while (S.size()>1 && orientation(nextToTop(S), S.top(), points[i]) != 2){
            S.pop();
        }
        S.push(points[i]);
    }


    // Agora a pilha tem os pontos de saída, imprime o conteúdo da pilha
    while(!S.empty()){
        Point p = S.top();
        cout << "(" << p.x << ", " << p.y <<")" << endl;
        S.pop();
    }
}