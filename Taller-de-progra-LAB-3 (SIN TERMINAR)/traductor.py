#Descripcion: programa que traduce ejemplos de mochila disponibles en https://github.com/JorikJooken/knapsackProblemInstances/tree/master, a 
# un formato de entrada aceptado por Simplex.

NombreArchivo = input("Ingrese el nombre del archivo: ")
NombreArchivoFinal = input("Ingrese el nombre del archivo de salida(escribir con .txt): ")
with open(NombreArchivo, "r") as file:
    Numvariables = int(file.readline().split()[0])
    print("Número de variables: ", Numvariables)
    listaPesos = [0]
    listaValores = [0]

    ## Se lee el archivo y se guardan los valores de los pesos y valores en listas
    for i in range(0, Numvariables):
        objeto = file.readline().split()
        listaValores.append(float(objeto[1]))
        listaPesos.append(float(objeto[2]))

    ## Se lee el peso total de la mochila, el cual esta en la ultima linea del archivo
    PesoTotalMochila = float(file.readline().split()[0])

    ## Si se desea ver los valores de los pesos y valores, descomentar las siguientes líneas
    #print("Pesos: ", listaPesos)
    #print("Valores: ", listaValores)

    ## Se crea la primera linea del archivo de salida
    listaPrimeraLinea = [Numvariables+1, 0, 0]

    #print(PesoTotalMochila)

    listaPesos[0] = PesoTotalMochila
    file.close()

    ## Se escribe el archivo de salida
    with open(NombreArchivoFinal, "w") as file:
        # Se crea el archivo de salida con el formato aceptado por Simplex

        file.write(str(listaPrimeraLinea[0]) + " " + str(listaPrimeraLinea[1]) + " " + str(listaPrimeraLinea[2]) + "\n")

        for i in range(0, Numvariables+1):
            file.write(str(listaValores[i]))
            if i != Numvariables:
                file.write(" ")
        file.write("\n")
        for i in range(0, Numvariables+1):
            if i == 0:
                file.write(str(listaPesos[i]))
            else:
                file.write(str(-listaPesos[i]))
            if i != Numvariables:
                file.write(" ")
        file.write("\n")

        ## Se crea la matriz de restricciones Iniciales tipo Xi <= 1
        for i in range(1, Numvariables+1):
            for j in range(0, Numvariables+1):
                if j == 0:
                    file.write("1")
                elif j == i:
                    file.write("-1")
                else:
                    file.write("0")
                if j != Numvariables:
                    file.write(" ")
            if(i != Numvariables):
                file.write("\n")
        file.close()