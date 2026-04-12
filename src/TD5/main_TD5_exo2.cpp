#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <algorithm>

enum Direction {
    Haut,
    Droit,
    Bas,
    Gauche,
};

struct Position {
    int x;
    int y;
};

namespace std {
    template <>
    struct hash<Position> {
        std::size_t operator()(Position const& pos) const {
            return std::hash<int>()(pos.x) ^ std::hash<int>()(pos.y);
        }
    };
}

struct Input_Structure {
    Position guardPos;
    Direction guardDir;

    std::vector<Position> obstaclesPos;
};

struct WalkResult {
    Position final_position;
    size_t steps_taken;
    std::unordered_set<Position> visited_positions;
};

int maxWidth { 0 };
int maxHeight { 0 };

bool operator==(Position const& a, Position const& b) {
    return a.x == b.x && a.y == b.y;
}

std::ostream& operator<<(std::ostream& os, Position const& a) {
    return os << "(" << a.x << ", " << a.y << ")";
}

void operator+=(Position& a, Position const& b) {;
    a.x = a.x + b.x;
    a.y = a.y + b.y;
}

Position operator+(Position const& a, Direction const& direction) {
    Position newPosition { a };

    switch (direction) {
        case Direction::Haut:
            newPosition.y = newPosition.y - 1;
            break;

        case Direction::Bas:
            newPosition.y = newPosition.y + 1;
            break;

        case Direction::Gauche:
            newPosition.x = newPosition.x - 1;
            break;

        case Direction::Droit:
            newPosition.x = newPosition.x + 1;
            break;
        
        default:
            break;
    }

    return newPosition;
}

void operator+=(Position& a, Direction const& direction) {
    a = a + direction;
};

Direction turn_right(Direction const& direction) {
    switch (direction) {
        case Direction::Haut:
            return Direction::Droit;

        case Direction::Droit:
            return Direction::Bas;

        case Direction::Bas:
            return Direction::Gauche;

        case Direction::Gauche:
            return Direction::Haut;
        
        default:
            break;
    }
}

Input_Structure read_input(std::istream& input_stream) {
    Input_Structure currentMap {};
    int lineNumber { 0 };

    for (std::string line{}; std::getline(input_stream, line, '\n') and line != "";) {
        if(lineNumber == 0) {
            maxWidth = line.length() - 1;
        }

        for(int i { 0 }; i < line.length() ; i++) {
            switch (line[i])
            {
            case '#':
                currentMap.obstaclesPos.push_back({ i, lineNumber });
                break;

            case '^':
                currentMap.guardPos = { i, lineNumber };
                currentMap.guardDir = Direction::Haut;
                break;

            case 'v':
                currentMap.guardPos = { i, lineNumber };
                currentMap.guardDir = Direction::Bas;
                break;

            case '<':
                currentMap.guardPos = { i, lineNumber };
                currentMap.guardDir = Direction::Gauche;
            break;
                
            case '>':
                currentMap.guardPos = { i, lineNumber };
                currentMap.guardDir = Direction::Droit;
                break;
                
            default:
                break;
            }
        }
        lineNumber++;
    }
    maxHeight = lineNumber - 1;
    return currentMap;
}

WalkResult simulation(Input_Structure const& input) {
    WalkResult results {};
    results.final_position = input.guardPos;
    
    Direction guardDir = input.guardDir;
    bool isNotOutOfBound { true };

    while (isNotOutOfBound) {
        if(std::find(input.obstaclesPos.begin(), input.obstaclesPos.end(),  results.final_position + guardDir) != input.obstaclesPos.end()) {
            guardDir = turn_right(guardDir);
        }

        results.final_position += guardDir;
        results.steps_taken++;

        if(results.final_position.x <= maxWidth && results.final_position.y <= maxHeight && results.final_position.x >= 0 && results.final_position.y >= 0) {
            results.visited_positions.insert(results.final_position);
        } else {
            isNotOutOfBound = false;
        }
    }

    return results;
};

/******************************************************************************************/
// J'ai juste fais le début de la question 4, je n'ai pas fait le test de positionnement des obstacles
struct GuardState
{
    Position position;
    Direction direction;
};

namespace std {
    template <>
    struct hash<GuardState> {
        std::size_t operator()(GuardState const& guard) const {
            return std::hash<int>()(guard.position.x) ^ std::hash<int>()(guard.position.y);
        }
    };
}

bool operator==(GuardState const& a, GuardState const& b) {
    return a.position == b.position;
};

/******************************************************************************************/


int main() {
    std::ifstream file("../../map.txt");
    Input_Structure map = read_input(file);

    WalkResult results = simulation(map);

    std::cout << "Position finale : " << results.final_position << std::endl;
    std::cout << "Nombre de position : " << results.steps_taken << std::endl;
    std::cout << "Nombre de position differentes : " << results.visited_positions.size() << std::endl;

    return 0;
}