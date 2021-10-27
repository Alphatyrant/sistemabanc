# Configurações basicas da aplicação
APP_NAME		?= projeto1.out
VERSION     	?= \"V2.0.0\"
PROFILE        	?= debug

# Estrutura de arquivos do projeto
OUT_DIR        	?= out
BLD_DIR        	?= build
INC_FOLD    	?= inc
SRC_FILE    	?= $(wildcard ./src/*.c)
#OBJ_FILE    	= $(subst .c,.o,$(subst src,OUT_DIR,$(SRC_FILE)))

# Configuração do ambite de compição
CC ?= 			gcc

# Flags da compilação
CFLAGS +=     	${addprefix -I , ${INC_FOLD}}
CFLAGS +=     	${addprefix -D VERSAO=, ${VERSION}}

ifeq ($(PROFILE), release)
CFLAGS +=		-g0
CFLAGS +=		-O3
CFLAGS +=		-s
else
CFLAGS +=		-g3
CFLAGS +=		-O0
endif

.PHONY: all clean

all: help ${BLD_DIR}/${APP_NAME} 

${BLD_DIR}/${APP_NAME}:
	${CC} ${SRC_FILE} ${CFLAGS} -o ${BLD_DIR}/${APP_NAME}

run:
	./${BLD_DIR}/${APP_NAME}

clean:
	rm -rf ${BLD_DIR}/${APP_NAME}
	
help:
	@echo "APP_NAME:\t${APP_NAME}"
	@echo "VERSION: \t${VERSION}"
	@echo "PROFILE: \t${PROFILE}"