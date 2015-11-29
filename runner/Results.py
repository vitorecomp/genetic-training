
import json

class Result:
    jsonFile = ""
    jsonFileName = ""

    def __init__(self, jsonName):
        print("=================================================================")
        print(jsonName)
        print("=================================================================")
        self.jsonFileName = jsonName;
        self.openFile();

    def openFile(self):
        arqui = open(self.jsonFileName,"r")
        jsonInter = arqui.read();
        arqui.close()

        jsonInter = json.loads(jsonInter)
        self.jsonFile = jsonInter["execu"]

    def makeTimeTables(self):
        self.makeGlobalTime()
        #self.makeMemoTime()
        #self.makeProcessorTime();

    def makeSpeedUpTables(self):
        if self.hasArgument("num_threads"):
            self.makeSpeedUp();
        return

    def makeEfficienceTables(self):
        if self.hasArgument("num_threads"):
            self.makeEfficience()
        return

    def makeChunckTables(self):
        if self.hasArgument("chunck"):
            self.makeChunck()
        return



    def hasArgument(self, arg):
        if arg in self.jsonFile[0]:
            return True
        return False

    '''
    Especificas
    '''

    def makeTable(self, rows, cols):
        matriz = Matrix = [[0 for x in range(rows)] for x in range(cols)]
        return matriz

    def makeTime(self, times):
        total = 0;
        for i in times:
            total += i
        return total/len(times)

    def makeRes(self, name):
        i = name.find("./results/") + len("./results/")
        j = name[i:].find(".") + i
        return int(name[i:j])

    threads_dict = {
        "2":0,
        "4":1,
        "6":2,
        "8":3,
        "16":4,
        "32":5,
        "64":6
    }

    threads_dict2 = {
        "2":0,
        "4":1,
        "8":2,
        "16":3,
        "32":4,
        "64":5
    }

    inputDict = {
        "./results/4.txt":0,
        "./results/8.txt":1,
        "./results/16.txt":2,
        "./results/32.txt":3,
        "./results/64.txt":4,
        "./results/128.txt":5,
        "./results/256.txt":6,
        "./results/512.txt":7,
        "./results/1024.txt":8,
        "./results/2048.txt":9,
        "./results/4096.txt":10,
        "./results/8192.txt":11,
        "./results/16384.txt":12,
        "./results/32768.txt":13,
        "./results/65536.txt":14,
        "./results/131072.txt":15,
        "./results/262144.txt":16,
        "./results/524288.txt":17
    }

    chunck_dict = {
        "-1":0,
        "10":0,
        "20":1,
        "50":2,
        "100":3,
        "250":4,
        "500":5,
        "1000":6,
        "2500":7,
        "5000":8,
        "10000":9
    }

    dict_threads = [
        1 , 2, 4, 6, 8
    ]

    def makeGlobalTime(self):
        print("%=================================================================")
        print("%Global Time")
        print("%=================================================================")
        maxj = 1
        maxi = 1
        div = 1
        if self.hasArgument("process"):
            k = 2
            maxj = 7
            maxi = 18
        if self.hasArgument("process_2"):
            k = 6
            maxj = 6
            maxi = 14

        matriz = self.makeTable(maxj, maxi);

        for execu in self.jsonFile:
            x = self.inputDict[execu["input"]]
            if self.hasArgument("process"):
                y = self.threads_dict[execu["process"]]
            else:
                y = 0;
            if self.hasArgument("process_2"):
                y = self.threads_dict2[execu["process_2"]]
                x -= 4

            matriz[x][y] = self.makeTime(execu["times"])

        string = ""
        for i in range(maxi):
            res = pow(2, i + k)
            string += str(res)  + " numeros & "
            for j in range(maxj-1):
                string += " " + str(round(matriz[i][j]/div, 1)) + " &"
            string += " " + str(round(matriz[i][maxj-1]/div, 1)) + " \\\\ \hline"
            string += "\n"

        print(string)
        self.globalMatriz = matriz

    def makeMemoTime(self):
        print("%=================================================================")
        print("%Memo Time")
        print("%=================================================================")
        maxj = 1
        div =1
        if self.hasArgument("num_threads"):
            maxj = 5
        matriz = self.makeTable(maxj, 9);

        for execu in self.jsonFile:
            if execu["time_to_mesure"] == "-memo_geral":
                x = int(self.makeRes(execu["input_out_image"])/1000)
                if self.hasArgument("num_threads"):
                    y = self.threads_dict[execu["num_threads"]]
                else:
                    y = 0;
                matriz[x][y] = self.makeTime(execu["times"])
        string = ""
        for i in range(9):
            res = i*1000
            string += str(res) + "px X " + str(res) + "px &"
            for j in range(maxj-1):
                string += " " + str(round(matriz[i][j]/div, 1)) + " &"
            string += " " + str(round(matriz[i][maxj-1]/div, 1)) + " // /hline"
            string += "\n"

        print(string)
        self.memoMatriz = matriz

    def makeProcessorTime(self):
        print("%=================================================================")
        print("%Processor Time")
        print("%=================================================================")
        maxj = 1
        div = 1
        if self.hasArgument("num_threads"):
            maxj = 5
        if self.hasArgument("chunck"):
            div = 1000
            maxj = 10
        matriz = self.makeTable(maxj, 9);

        for execu in self.jsonFile:
            if execu["time_to_mesure"] == "-filter":
                x = int(self.makeRes(execu["input_out_image"])/1000)
                if self.hasArgument("num_threads"):
                    y = self.threads_dict[execu["num_threads"]]
                else:
                    y = 0;
                if self.hasArgument("chunck"):
                    y = self.chunck_dict[execu["chunck"]]

                matriz[x][y] = self.makeTime(execu["times"])
        string = ""
        for i in range(9):
            res = i*1000
            string += str(res) + "px X " + str(res) + "px &"
            for j in range(maxj-1):
                string += " " + str(round(matriz[i][j]/div, 1)) + " &"
            string += " " + str(round(matriz[i][maxj-1]/div, 1)) + " // /hline"
            string += "\n"

        print(string)
        self.processorMatriz = matriz

    def makeSpeedUp(self):
        print("%=================================================================")
        print("%SpeedUp")
        print("%=================================================================")
        string = ""
        maxj = 5
        matrizi = self.makeTable(maxj, 9);
        matriz = self.processorMatriz
        for i in range(9):
            if i == 0:
                continue
            if 0 == matriz[i][0] :
                continue


            res = i*1000
            string += str(res) + "px X " + str(res) + "px &"
            for j in range(maxj-1):
                matrizi[i][j] = matriz[i][0]/matriz[i][j]
                string += " " + str(round(matriz[i][0]/matriz[i][j], 2)) + " &"
            matrizi[i][maxj-1] = matriz[i][0]/matriz[i][maxj-1]
            string += " " + str(round(matriz[i][0]/matriz[i][maxj-1], 2)) + " // /hline"
            string += "\n"

        print(string)
        self.speedUpMatrizP = matrizi
        matrizi = self.makeTable(maxj, 9);
        print("%=================================================================")
        print("%SpeedUp Global")
        print("%=================================================================")
        string = ""
        maxj = 5
        matriz = self.globalMatriz
        for i in range(9):
            if i == 0:
                continue
            if 0 == matriz[i][0] :
                continue

            res = i*1000
            string += str(res) + "px X " + str(res) + "px &"
            for j in range(maxj-1):
                matrizi[i][j] = matriz[i][0]/matriz[i][j]
                string += " " + str(round(matriz[i][0]/matriz[i][j], 2)) + " &"
            matrizi[i][maxj-1] = matriz[i][0]/matriz[i][maxj-1]
            string += " " + str(round(matriz[i][0]/matriz[i][maxj-1], 2)) + " // /hline"
            string += "\n"

        print(string)
        self.speedUpMatrizG = matrizi

    def makeEfficience(self):
        print("%=================================================================")
        print("%Efficience")
        print("%=================================================================")
        string = ""
        maxj = 5
        matrizi = self.makeTable(maxj, 9);
        matriz = self.speedUpMatrizP
        for i in range(9):
            if i == 0:
                continue
            if 0 == matriz[i][0] :
                continue
            res = i*1000
            string += str(res) + "px X " + str(res) + "px &"
            for j in range(maxj-1):
                matrizi[i][j] = matriz[i][j]/self.dict_threads[j]
                string += " " + str(round(matriz[i][j]/self.dict_threads[j], 2)) + " &"
            matrizi[i][maxj-1] = matriz[i][maxj-1]//self.dict_threads[maxj-1]
            string += " " + str(round(matriz[i][maxj-1]/self.dict_threads[maxj-1], 2)) + " // /hline"
            string += "\n"

        print(string)
        self.eff = matrizi

        print("%=================================================================")
        print("%Efficencia global")
        print("%=================================================================")
        string = ""
        maxj = 5
        matriz = self.speedUpMatrizG
        for i in range(9):
            if i == 0:
                continue
            if 0 == matriz[i][0] :
                continue
            res = i*1000
            string += str(res) + "px X " + str(res) + "px &"
            for j in range(maxj-1):
                matrizi[i][j] = matriz[i][j]/self.dict_threads[j]
                string += " " + str(round(matriz[i][j]/self.dict_threads[j], 2)) + " &"
            matrizi[i][maxj-1] = matriz[i][maxj-1]//self.dict_threads[maxj-1]
            string += " " + str(round(matriz[i][maxj-1]/self.dict_threads[maxj-1], 2)) + " // /hline"
            string += "\n"

        print(string)
        self.effG = matrizi

    def makeChunck(self):
        pass

    def makeGrapths(self):
        pass
