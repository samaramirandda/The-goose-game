// Game
#include "characters.h"

#include "questions.h"
QuestionController Questions = { questionExists, createQuestion, newQuestion, saveQuestionToFile, refreshQuestionsFile, loadQuestions, listQuestions, removeQuestion, freeQuestions, getRandomQuestion, askQuestion };

#include "board.h"
BoardController Board = { getBoardSize, generateGameBoard, printGameBoard };

#include "player.h"
PlayerController Player = { getPosition, movePlayer };

#include "game.h"
GameController Game = { checkVictory, saveGame, end, start, lastResults };
