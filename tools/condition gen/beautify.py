a = []

for i in range(2):
    for j in range(2):
        for k in range(2):
            for l in range(2):
                for m in range(2):
                    for n in range(2):
                        for o in range(2):
                            for p in range(2):
                                string = "if(this->side == ("
                                string += "(int) TileSide::TOP | " if i == 1 else ""
                                string += "(int) TileSide::BOTTOM | " if j == 1 else ""
                                string += "(int) TileSide::RIGHT | " if k == 1 else ""
                                string += "(int) TileSide::LEFT | " if l == 1 else ""
                                string += "(int) TileSide::TOP_LEFT | " if m == 1 else ""
                                string += "(int) TileSide::TOP_RIGHT | " if n == 1 else ""
                                string += "(int) TileSide::BOTTOM_LEFT | " if o == 1 else ""
                                string += "(int) TileSide::BOTTOM_RIGHT | " if p == 1 else ""
                                string = string.replace(' ', '')[:-2].upper()
                                string += ")"
                                a.append(string)

with open("output.txt", "w+") as lol:
    for i in range(len(a)):
        lol.write(a[i] + "\n")
        print i
