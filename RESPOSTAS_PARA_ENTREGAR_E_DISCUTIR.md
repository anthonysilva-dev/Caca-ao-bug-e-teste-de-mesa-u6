# Respostas da Parte B e Discussão Final (Unidade 6)

## L1. `static` na prática: um gerador de IDs
* **Teste extra:** Depois teste: tire o `static` e veja o que muda.
* **Resposta:** Sem o `static`, a saída deixa de ser `1 2 3 4 5` e passa a ser **`1 1 1 1 1`**, pois `id` vira uma variável local comum na pilha (stack), sendo recriada e zerada a cada chamada de `proximo_id()`.

---

## L3. Uma função que devolve um bloco do heap
* **Pergunta:** Pense: por que aqui devolver o ponteiro é certo (e devolver `&x` de uma variável local seria errado, como no item 4 da Parte A)? Quem fica responsável pelo `free`?
* **Resposta:** Porque o vetor foi alocado no **heap** com `malloc`, e blocos no heap continuam existindo até que `free` seja chamado (diferente de uma variável local na pilha, que é destruída quando a função retorna). Quem fica responsável pelo `free` é a função chamadora (`main`), que recebe o ponteiro e libera a memória após terminar de usá-la.

---

## L4. Caçar um vazamento com a ferramenta
* **Pergunta:** Sem a ferramenta, dá para perceber o vazamento só rodando? Quantos bytes vazaram?
* **Resposta:** Não dá para perceber apenas rodando o programa normalmente, porque ele termina sem erros visíveis e o sistema operacional recupera a memória ao encerrar o processo (o problema só ficaria evidente em programas contínuos que alocam memória repetidamente). Vazaram **4.000 bytes** (`1000 * sizeof(int)`, considerando `int` de 4 bytes).

---

## L5. Uso após liberar, flagrado pelo AddressSanitizer
* **Pergunta:** Qual a diferença entre este erro e o vazamento do L4? (Dica: um usa memória que já devolveu; o outro nunca devolve a memória.)
* **Resposta:** No **uso após liberação (`heap-use-after-free`, L5)**, o programa devolve a memória ao sistema com `free`, mas continua acessando aquele endereço inválido, o que pode ler lixo, corromper dados ou causar falha imediata. Já no **vazamento de memória (`memory leak`, L4)**, o programa nunca chama `free`, deixando o bloco ocupado sem uso e desperdiçando memória enquanto estiver rodando.

---

## Para discutir no fim
* **Pergunta:** Quais bugs o compilador pega sozinho (com `-Wall -Wextra`)? Quais só aparecem ao rodar ou com uma ferramenta como o AddressSanitizer/Valgrind?
* **Resposta:**
  * **Pego pelo compilador (erro ou warning com `-Wall -Wextra`):**
    * **Item 12 (Parte A):** erro de compilação ao tentar usar `i` ou `dobro` fora do bloco do `for` (fora de escopo).
    * **Item 4 (Parte A):** *warning* (`-Wreturn-local-addr`) ao retornar o endereço `&x` de uma variável local da pilha.
  * **Só aparece ao rodar ou com ferramentas de memória (AddressSanitizer / Valgrind):**
    * **Itens 1, 2, 7 (Parte A) e L1:** erros lógicos de tempo de vida. Esquecer `static` faz a variável reiniciar a cada chamada, mas isso é código C válido.
    * **Itens 6, 8, 11 (Parte A) e L4, L5:** erros dinâmicos no heap, como vazamento de memória (`memory leak`, item 8 e L4), uso após liberação (`use-after-free`, item 6 e L5) e liberação dupla (`double free`, item 11). Esses problemas compilam sem erro e só são flagrados em execução ou com ferramentas de análise.
