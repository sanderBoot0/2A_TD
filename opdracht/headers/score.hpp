/**
 * @file score.hpp
 * @brief This file contains the declaration and definition of the hits struct and score class
 * 
 */

#ifndef SCORE_HPP
#define SCORE_HPP

/**
 * @brief This struct contains the playernumber and firepower of the enemy when hit
 * 
 */
struct hits {
    int playerID;
    int damage;
};
/**
 * @brief this class contains the score and the hits that the player took during the game 
 * 
 */
class score {
   private:
    int score = 100;
    hits score_hits[100];

    int n_hits = 0;

   public:
/**
 * @brief Get the Score object
 * 
 * @return int 
 */
    int getScore() {
        return score;
    }
/**
 * @brief this functions adds the enemy playerID and the dmg you took to the score_hits[] array
 * 
 * @param playerID 
 * @param damage 
 */
    void addHit(uint8_t playerID, uint8_t damage) {
        score_hits[n_hits] = {playerID, damage};
        if(score_hits[n_hits].damage < 0) {
            score_hits[n_hits].damage = 0;
        }
        n_hits++;
        score -= damage;
    }
/**
 * @brief Get the Hit object
 * 
 * @param index 
 * @return hits 
 */
    hits getHit(int index) {
        if(index > n_hits)
            return {0, 0};

        return score_hits[index];
    }
};

#endif // SCORE_HPP