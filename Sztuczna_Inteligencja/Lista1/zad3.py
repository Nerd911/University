import itertools
import random

HIGHER_CARD = 0
ONE_PAIR = 1
TWO_PAIR = 2
THREE_OF_A_KIND = 3
STRAIGHT = 4
FLUSH = 5
FULL_HOUSE = 6
FOUR_OF_A_KIND = 7
STRAIGHT_FLUSH = 8

def are_same_color(cards):
    colors = {card[1] for card in cards}
    return len(colors) == 1
def is_sequence(cards):
    figs = [card[0] for card in cards]
    for i in range(1, 5):
        if figs[i] - 1 != figs[i-1]:
            return False
    return True

def count_figs(cards):
    dic = dict()
    for card in cards:
        if not card[0] in dic:
            dic[card[0]] = 0
        dic[card[0]]+=1
    result = [val for val in dic.values()]
    result.sort()
    return result

def get_hand(cards):
    cards.sort()
    col = are_same_color(cards)
    seq = is_sequence(cards)
    if col:
        if seq:
            return STRAIGHT_FLUSH
        return FLUSH
    if seq:
        return STRAIGHT
    counts = count_figs(cards)
    if counts == [1, 2, 2]:
        return TWO_PAIR
    if counts == [1, 1, 1, 2]:
        return ONE_PAIR
    if counts == [2, 3]:
        return FULL_HOUSE
    if counts == [1, 4]:
        return FOUR_OF_A_KIND
    if counts == [1, 1, 3]:
        return THREE_OF_A_KIND
    return HIGHER_CARD

def compare(fig_cards, blot_cards):
    fig_hand = get_hand(fig_cards)
    blot_hand = get_hand(blot_cards)
    # print(fig_hand)
    # print(blot_hand)

    if fig_hand != blot_hand:
        return fig_hand - blot_hand
    return 1

def random_combination(iterable, r):
    pool = tuple(iterable)
    n = len(pool)
    indices = sorted(random.sample(range(n), r))
    return [pool[i] for i in indices]

def get_chances(fig_deck, blot_deck):
    cntr = 0
    for i in range(0, 100000):
        fig_cards = random_combination(fig_deck, 5)
        blot_cards = random_combination(blot_deck, 5)
        # print(fig_cards)
        # print(blot_cards)
        if compare(fig_cards, blot_cards) > 0:
            cntr+=1
    return 1 - cntr/100000.0

def main():
    fig_deck = [x for x in itertools.product([i for i in range(11, 15)], [j for j in range(0, 4)])]
    blot_deck = [x for x in itertools.product([i for i in range(2, 11)], [j for j in range(0, 4)])]
    print(get_chances(fig_deck, blot_deck))

    # best_deck = []
    # n = len(blot_deck)
    # for i in range(5, n):
    #     combinations = itertools.combinations(blot_deck, i)
    #     for combination in combinations:
    #         chances = get_chances(fig_deck, combination)
    #         if chances > 0.5:
    #             best_deck = combination
    #             print(len(best_deck))
    #             break
    # print(best_deck)

if __name__ == "__main__":
    main()
