#ifndef SCORE_HPP
#define SCORE_HPP

struct hits {
    int playerID;
    int damage;
};

class score {
   private:
    int score = 100;
    hits score_hits[100];

    int n_hits = 0;

   public:

    int getScore() {
        return score;
    }

    void addHit(uint8_t playerID, uint8_t damage) {
        score_hits[n_hits] = {playerID, damage};
        if(score_hits[n_hits].damage < 0) {
            score_hits[n_hits].damage = 0;
        }
        n_hits++;
        score -= damage;
    }

    hits getHit(int index) {
        if(index > n_hits)
            return {0, 0};

        return score_hits[index];
    }
};

#endif // SCORE_HPP