.PHONY = all

CC = g++

SRCS := main.cpp card.cpp
OUT := vbj

all: buildgame

buildgame:
	@echo "Building vBlackJack"
	${CC} -o ${OUT} ${SRCS}