def selection_sort(vetor: int, n: int):
    
    for k in range(n - 1, 0, -1):

        imax = 0

        for i in range(1, k + 1):
            if vetor[imax] < vetor[i]:
                imax  = i

        vetor[k], vetor[imax] = vetor[imax], vetor[k]

vetor: list[int] = []
n: int = 10

print("Digite 10 numeros para o vetor:")
for i in range(n):
    vetor.append(int(input(f"vetor[{i}]: ")))

print(f"\nVetor antes:")
for i in range(n):
    print(vetor[i], end=" ")

selection_sort(vetor, n)

print(f"\nVetor depois:")
for i in range(n):
    print(vetor[i], end=" ")