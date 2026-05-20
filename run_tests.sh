#!/bin/bash

OUTPUT="resultados.csv"

echo "algoritmo,nproc,quantum,execucao,tme" > $OUTPUT

algoritmos=(
    "fifo"
    "sjf"
    "ljf"
    "prio_static"
    "prio_dynamic"
    "prio_dynamic_quantum"
)

quantums=(10 20 30)

nprocs=(10 20 30 40 50 60 70 80 90 100)

for algoritmo in "${algoritmos[@]}"
do
    executavel="./main_${algoritmo}"

    for quantum in "${quantums[@]}"
    do
        for nproc in "${nprocs[@]}"
        do
            for execucao in $(seq 1 30)
            do
                echo "Executando: $algoritmo | N=$nproc | Q=$quantum | Exec=$execucao"

                saida=$($executavel -n $nproc -q $quantum)

                tme=$(echo "$saida" | grep "TME:" | awk '{print $2}')

                echo "$algoritmo,$nproc,$quantum,$execucao,$tme" >> $OUTPUT
            done
        done
    done
done

echo "Testes finalizados."