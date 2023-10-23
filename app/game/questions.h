typedef enum
{
    MULTIPLE_CHOICE,
    TRUE_FALSE,
    DIRECT_RESPONSE
} QuestionType;

typedef struct Question
{
    int id;
    char question[100];
    QuestionType type;
    char options[4][50]; // For multiple choice questions
    char answer[50];     // For direct response and true/false questions
    bool asked;
    struct Question *prev;
    struct Question *next;
} Question;

typedef struct questionController
{
    bool (*questionExists)(int id);
    Question *(*createQuestion)(char question[], QuestionType type);
    void (*newQuestion)();
    void (*saveQuestionToFile)(Question *question);
    void (*refreshQuestionsFile)();
    void (*loadQuestions)();
    void (*listQuestions)();
    void (*removeQuestion)();
    void (*freeQuestions)();

    // Game related
    Question *(*getRandomQuestion)();
    bool (*askQuestion)();
} QuestionController;

Question *firstQuestion = NULL, *lastQuestion = NULL;

#include "questions.c"