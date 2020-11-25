#Copyright 2020 Matthew Macallister
#
#This file is part of ProgrammingChallengeLib.
#
#ProgrammingChallengeLib is free software: you can redistribute it and/or
#modify it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#ProgrammingChallengeLib is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with ProgrammingChallengeLib.  If not, see
#<https://www.gnu.org/licenses/>.



import multiDimArray as md

#lol = md.zeros((1,2))
lol = md.full((4,2,3), "asd")

#lol[0] = 'dsa'

#print (lol[1]._contents, lol[1,0]._contents, lol[1,1]._contents, lol[2,0,2])
print (lol[0]._contents, lol[1]._contents, lol[2]._contents, lol[3]._contents)
print (lol[1][0]._contents, lol[1,1]._contents)
print (lol[1:3]._contents, lol[1][1][1], lol[1][1][2])

print (str("1234")[1:3])
