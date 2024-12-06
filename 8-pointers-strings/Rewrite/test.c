#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *s1 = "rkyntalnokutnceuooyknmkitgaiabglcqhbxsobfkgwmrliktohkufaiduqselexesoxxwooilozkakmcktwohjozpwdjtdqkhtdnulnlomomxfqshqgzebkxfjegszyzcakrgskdrdhrcxbginmfjydmgzanznuhrechexmwzxichyylnlfgklrvyrzywdzvfzusksftxnavrnvaozbyqbiqokgzcmjaptpstgghxtzadfsunjfbptujwwenlowzlupzsxwdsexjmfvyrejyuvbanjbwvekbquhpydtleyystaykksmswlfvqwcdvmsrzcninfdldcwwpqqxsoblnyboqxwgwbybphwyutesyqsncovpybjvpohpntzmvdnchonkligzwzgjapqtgrlsgaldagyrejjuvvxmfheqpyuohhbktrabhrjwmxxcwaiilbchtllrnvogdcgudutremsngyuvekepbkgxwqcwebmjomhjdiuvvdrmqeeaxuwmtkukcigwmmtxivikqebabpzwuwgsrvakzkewoorkgjaabykdvepwtxvsfnxhgyoownpmkcqpohpjdqclivnpuawxiusmqcyqgxvrhwddhxetaecoybnsdnpuzpcvjngvcdkgkfwyhbbgrneaauyugsnnqwyfocqubemotessbklhfuspipvfhsumcrhoreaowdcusnkfkylerkyfehsdjaaycbwuvswldfxzthigmgfwpvcqzkxqzqtqlkycqkzvwzlxkphmuknhwxhjmatwguxjwrqjunuzyntdlfgmpeecptsyaqknnutflqesbelqvmeljjlpfaryuvyusuqrktxrgkaewyaaaoumtbqkuhylyrxdusxjnirlczpvzoazmmqmnkvpabcxtmgkmlhzwfwbkvyvaiyyzebooujncxywacgsqguwcgjlwabaquzvmvhrqxacotfuwdcnrbnncegyfqufegmrkfmlsndnnknmfkmvedonrubjdeqiqbpojclullyglzumgjzhcycejfarbeypvbkmnjfyquuaecvhjirgthrpmxhcmkbdjektvruhzqsgfbfgjneqvwufhvlwdhuhqhjefieeigcqetohecfmpicqwismuxyfvddcbcknlrqyvedgifgppvhvuhlgbepetrpaytfhqnxvcawhbauawbdyizegzcrtpossytsxjdcepwfsorghmmcxlevkxefihdnkxpujhuislhsplerskyxspfrbmbeubzwvfkweirwyizzyfibovjcplyhirsjwqwmkhgrpnyhvsqoeqeemgdtmvyhunwtkyaqmldhskncmyixwcxmnkhflfeapfocdmgvpoluivrzzrbmptqxlogixkxxnwopvoiluocfchcsnczgqcdwrhskdxgxkihavqtbprbpqtgmxwrfvaoqyqyqwxsawawsleqlxupgbbweixivaymlswaldpucvwlharizvnoonihmdladavogouqkkwsihaobluxnnjheidlcevhnxzjpobwvnsnkiolegobghkykpzopvcxrmblwmanfeylkivlqcdjnzrbpbaynctwvnukuuwydfiskysqgtsloymlhlywneoacposyoolcgoqfazaxvsehtcxvalxlyceojbqnumivlpvukvctkbtugujeeypxovcyzsosvpgxjvautkaxwasepspvlbtormxpdfnbnovdvudekddudobhsjngicvndoganpedhooniowjlikgtvlelwsqhuxlxwsnryrjzxmeiqrkwiynxezknvksezhnlvlthopxytfbgrwgppkgdzstzvmvutskoyndikvrnoixqcuhpipyibjwujsvzuiducbdszxeuamtpficggcrk";
char *s2 = "rkyntalnokutnceuooyknmkitgaiabglcqhbxsobfkgwmrliktohkufaiduqselexesoxxwooilozkakmcktwohjozpwdjtdqkhtdnulnlomomxfqshqgzebkxfjegszyzcakrgskdrdhrcxbginmfjydmgzanznuhrechexmwzxichyylnlfgklrvyrzywdzvfzusksftxnavrnvaozbyqbiqokgzcmjaptpstgghxtzadfsunjfbptujwwenlowzlupzsxwdsexjmfvyrejyuvbanjbwvekbquhpydtleyystaykksmswlfvqwcdvmsrzcninfdldcwwpqqxsoblnyboqxwgwbybphwyutesyqsncovpybjvpohpntzmvdnchonkligzwzgjapqtgrlsgaldagyrejjuvvxmfheqpyuohhbktrabhrjwmxxcwaiilbchtllrnvogdcgudutremsngyuvekepbkgxwqcwebmjomhjdiuvvdrmqeeaxuwmtkukcigwmmtxivikqebabpzwuwgsrvakzkewoorkgjaabykdvepwtxvsfnxhgyoownpmkcqpohpjdqclivnpuawxiusmqcyqgxvrhwddhxetaecoybnsdnpuzpcvjngvcdkgkfwyhbbgrneaauyugsnnqwyfocqubemotessbklhfuspipvfhsumcrhoreaowdcusnkfkylerkyfehsdjaaycbwuvswldfxzthigmgfwpvcqzkxqzqtqlkycqkzvwzlxkphmuknhwxhjmatwguxjwrqjunuzyntdlfgmpeecptsyaqknnutflqesbelqvmeljjlpfaryuvyusuqrktxrgkaewyaaaoumtbqkuhylyrxdusxjnirlczpvzoazmmqmnkvpabcxtmgkmlhzwfwbkvyvaiyyzeboozujncxywacgsqguwcgjlwabaquzvmvhrqxacotfuwdcnrbnncegyfqufegmrkfmlsndnnknmfkmvedonrubjdeqiqbpojclullyglzumgjzhcycejfarbeypvbkmnjfyquuaecvhjirgthrpmxhcmkbdjektvruhzqsgfbfgjneqvwufhvlwdhuhqhjefieeigcqetohecfmpicqwismuxyfvddcbcknlrqyvedgifgppvhvuhlgbepetrpaytfhqnxvcawhbauawbdyizegzcrtpossytsxjdcepwfsorghmmcxlevkxefihdnkxpujhuislhsplerskyxspfrbmbeubzwvfkweirwyizzyfibovjcplyhirsjwqwmkhgrpnyhvsqoeqeemgdtmvyhunwtkyaqmldhskncmyixwcxmnkhflfeapfocdmgvpoluivrzzrbmptqxlogixkxxnwopvoiluocfchcsnczgqcdwrhskdxgxkihavqtbprbpqtgmxwrfvaoqyqyqwxsawawsleqlxupgbbweixivaymlswaldpucvwlharizvnoonihmdladavogouqkkwsihaobluxnnjheidlcevhnxzjpobwvnsnkiolegobghkykpzopvcxrmblwmanfeylkivlqcdjnzrbpbaynctwvnukuuwydfiskysqgtsloymlhlywneoacposyoolcgoqfazaxvsehtcxvalxlyceojbqnumivlpvukvctkbtugujeeypxovcyzsosvpgxjvautkaxwasepspvlbtormxpdfnbnovdvudekddudobhsjngicvndoganpedhooniowjlikgtvlelwsqhuxlxwsnryrjzxmeiqrkwiynxezknvksezhnlvlthopxytfbgrwgppkgdzstzvmvutskoyndikvrnoixqcuhpipyibjwujsvzuiducbdszxeuamtpficggcrk";
char *t1 = "rkyntalnokutnceuooyknmkitgaiabglcqhbxsobfkgwmrliktohkufaiduqselexesoxxwooilozkakmcktwohjozpwdjtdqkhtdnulnlomomxfqshqgzebkxfjegszyzcakrgskdrdhrcxbginmfjydmgzanznuhrechexmwzxichyylnlfgklrvyrzywdzvfzusksftxnavrnvaozbyqbiqokgzcmjaptpstgghxtzadfsunjfbptujwwenlowzlupzsxwdsexjmfvyrejyuvbanjbwvekbquhpydtleyystaykksmswlfvqwcdvmsrzcninfdldcwwpqqxsoblnyboqxwgwbybphwyutesyqsncovpybjvpohpntzmvdnchonkligzwzgjapqtgrlsgaldagyrejjuvvxmfheqpyuohhbktrabhrjwmxxcwaiilbchtllrnvogdcgudutremsngyuvekepbkgxwqcwebmjomhjdiuvvdrmqeeaxuwmtkukcigwmmtxivikqebabpzwuwgsrvakzkewoorkgjaabykdvepwtxvsfnxhgyoownpmkcqpohpjdqclivnpuawxiusmqcyqgxvrhwddhxetaecoybnsdnpuzpcvjngvcdkgkfwyhbbgrneaauyugsnnqwyfocqubemotessbklhfuspipvfhsumcrhoreaowdcusnkfkylerkyfehsdjaaycbwuvswldfxzthigmgfwpvcqzkxqzqtqlkycqkzvwzlxkphmuknhwxhjmatwguxjwrqjunuzyntdlfgmpeecptsyaqknnutflqesbelqvmeljjlpfaryuvyusuqrktxrgkaewyaaaoumtbqkuhylyrxdusxjnirlczpvzoazmmqmnkvpabcxtmgkmlhzwfwbkvyvaiyyzeboo";
char *t2 = "ozujncxywacgsqguwcgjlwabaquzvmvhrqxacotfuwdcnrbnncegyfqufegmrkfmlsndnnknmfkmvedonrubjdeqiqbpojclullyglzumgjzhcycejfarbeypvbkmnjfyquuaecvhjirgthrpmxhcmkbdjektvruhzqsgfbfgjneqvwufhvlwdhuhqhjefieeigcqetohecfmpicqwismuxyfvddcbcknlrqyvedgifgppvhvuhlgbepetrpaytfhqnxvcawhbauawbdyizegzcrtpossytsxjdcepwfsorghmmcxlevkxefihdnkxpujhuislhsplerskyxspfrbmbeubzwvfkweirwyizzyfibovjcplyhirsjwqwmkhgrpnyhvsqoeqeemgdtmvyhunwtkyaqmldhskncmyixwcxmnkhflfeapfocdmgvpoluivrzzrbmptqxlogixkxxnwopvoiluocfchcsnczgqcdwrhskdxgxkihavqtbprbpqtgmxwrfvaoqyqyqwxsawawsleqlxupgbbweixivaymlswaldpucvwlharizvnoonihmdladavogouqkkwsihaobluxnnjheidlcevhnxzjpobwvnsnkiolegobghkykpzopvcxrmblwmanfeylkivlqcdjnzrbpbaynctwvnukuuwydfiskysqgtsloymlhlywneoacposyoolcgoqfazaxvsehtcxvalxlyceojbqnumivlpvukvctkbtugujeeypxovcyzsosvpgxjvautkaxwasepspvlbtormxpdfnbnovdvudekddudobhsjngicvndoganpedhooniowjlikgtvlelwsqhuxlxwsnryrjzxmeiqrkwiynxezknvksezhnlvlthopxytfbgrwgppkgdzstzvmvutskoyndikvrnoixqcuhpipyibjwujsvzuiducbdszxeuamtpficggcrk";

int main() {
    int i;
    for (i = 0; i < strlen(s1); ++i) {
        if (s1[i] != s2[i]) {
            printf("i = %d\n", i);
            break;;
        }
    }
    printf("s1 = %c\ns2 = %c", t1[i], t2[i]);
}