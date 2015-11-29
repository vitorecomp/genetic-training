
import json
import os
from Results import Result


class Argument:
    name = ""
    to_fill = False
    arguments = []

    def __init__(self, json_d):
        self.name = json_d["name"]
        self.to_fill = False
        self.arguments = []
        if json_d["type"] ==  "tofill":
            self.to_fill = True
            return

        if json_d["type"] == "list":
            self.arguments = json_d["values"]
            return

        if json_d["type"] == "build_list":
            start = json_d["values"][0]
            inter = json_d["values"][1]
            end = json_d["values"][2]
            while start < end:
                self.arguments += [start]
                start += inter

            if len(self.arguments) == 0:
              self.arguments += [start]
            return


class Program:
    name = ""
    name_to_save= ""
    arguments = []
    savedJsons = []

    def __init__(self, json_d):
        self.savedJsons = []
        self.name = json_d["name"]
        self.name_to_save = json_d["name_to_save"]
        self.arguments = []
        for i in json_d["arguments"]:
            argument = Argument(i)
            self.arguments += [argument]

    @staticmethod
    def read():
        file_j = open("./runner/programs.json","r")
        json_u = file_j.read()
        file_j.close()

        json_d = json.loads(json_u)
        return json_d["programs"]

    @staticmethod
    def getPrograms():
        programs = Program.read()
        print (len(programs));
        return Program.convert(programs);

    @staticmethod
    def convert(programs):
        list = []
        for i in programs:
            list += [Program(i)]
        return list;

    def execute(self, list_a):
        i = 0
        for argument in self.arguments:
            if argument.to_fill:
                argument.arguments = list_a[i]
                i += 1

        deep = len(self.arguments)
        program_exe = self.name
        json_to_save = {}
        json_to_save["program_name"] = self.name
        self.run_execution(0, program_exe, json_to_save)

    def readTime(self):
        f = open('time.txt', 'r')
        s_time = f.read()
        f.close()
        os.system("rm -f time.txt")
        return float(s_time)

    def exists(self, jsoninter):
        print("==============================")
        print(len(self.savedJsons))
        for i in self.savedJsons:
            exist = True
            for j in self.arguments:
                if jsoninter[j.name] != i[j.name]:
                    #print(jsoninter[j.name])
                    #print(i[j.name])
                    exist = False
            if exist:
                return True

        return False

    def run_execution(self, deep, program_exe, json_to_save):
        max = len(self.arguments);
        if (deep >= max):
            print(program_exe)
            if self.exists(json_to_save):
                print("Ja foi executado")
                return

            print("Executando")

            json_to_save["times"] = []
            os.system("rm -f time.txt")

            for i in range(0, 10, 1):
                print(i,end=" ",flush=True)
                os.system(program_exe + " >> time.txt")
                #os.system("echo 2 >> time.txt")
                time = self.readTime()
                json_to_save["times"].append(time)
            print(" ")
            self.append(json_to_save.copy());
            return

        else:
            name = self.arguments[deep].name
            deep_i = deep + 1
            for i in self.arguments[deep].arguments:
                program_exe_l = program_exe + " " + str(i)
                json_to_save[name] = str(i)
                self.run_execution(deep_i, program_exe_l, json_to_save)

            return



    def append(self, jsoninter):
        self.savedJsons.append(jsoninter.copy())
        self.save();
        return

    def save(self):
        if(len(self.savedJsons) == 0):
            return
        save_time = {}
        save_time["execu"] = self.savedJsons;
        valor = json.dumps(save_time, sort_keys=True, indent=4);
        f = open("./results/time/" + self.name_to_save + ".json", 'w')
        f.write(valor)
        f.close()

    def getExecuted(self):
        try:
            arqui = open("./results/time/" + self.name_to_save + ".json","r")
            jsoninter = arqui.read()
            arqui.close()
            jsoninter = json.loads(jsoninter)
            self.savedJsons = jsoninter["execu"]
        except:
            self.savedJsons = []

    def makeResults(self):
        result = Result("./results/time/" + self.name_to_save + ".json")
        result.makeTimeTables()
        result.makeSpeedUpTables()
        result.makeEfficienceTables()
        result.makeGrapths()
        result.makeChunckTables()
