#include "generator.h"
#include "timer.h"

// TODO: increase rand fuction RAND_MAX value.

std::string Generator::randName()
{
	std::string first[3] = { "The-","","" };
	std::string second[163] = { "","Antarctican","Flying","Electric","Fractured","Broken","Clear","Muddy","Yellow","Naked","Invisible","","Hollow","Crass","Light","Dark","Chocolate","Riff","","Mind","Heartless","Rock","Gods of","Sacrifice to","Master","Sleazy","Sisters of","Brothers of","Angry","Dying","Bloody","","Crazy","Shocking","Quiet","Sick","Cynical","Complete","Rude","Spicy","Hurt","Aquatic","Demonic","Obselete","Grieving","Deep","Ancient","Dead","Impossible","Violent","Juvenile","Real","Long","Meek","Orange","Grey","Moaning","","Jobless""Awful","Typical","Acid","Little","Obscene","Dry","Sticky","Rapid","Addictive","Cool","Tame","Royal","","Cruel","Loud","High","Big","Chemical","Mighty","Wretched","Drunk","General","Daily","Fluffy","Elfin","Two","Three","Scandalous","","Four","Five","Only","Sex","Rustic","Empty","Ugly","Evil","Disturbed","Unnatural","Ghostly","Heavy","","Modern","Fresh","Ragged","","Innocent","Acoustic","Rich","Lewd","Perverted","Infernal","Abusive","","Quick","Blue-eyed","Stormy","Icy","True","Chilly","Jaded","Black","Creepy","Screaming","Stabbing","Tilted","Spurned","Unreal","","Pissed","Awesome","Spinal","Dirty","Black","Scarlet","Gang of","Major","Headless","Tortured","Hybrid","Sonic","Riot","Hell","Damned","Pink","White","Green","Insidious","Spiritual","Broken","Abusive","Dark","Real","Enchanted","Imaginary","Daily","Lame","Future","Automatic","Shrill","Scarce","","Noctural","Asian","Streetlight" };
	std::string third[137] = { "Gods","Devil","Letter","Men","Ladies","Widow","Statement","Scarecrow","Chickens","Animal","Mice","Cheese","Punishment","Thrill","Pain","Death","Truth","Temper","Summer","Anarchy","Antichrist","Self","Face","Tears","Story","Blows","Invention","Inc.","Window","Thrones","Surgery","Metal","Meeks","Ancestors","Stoners","Spiders","Brothers","Sisters","Of Fate","Tramps","Behaviour","Road","Tree","Beetles","Sunday","Zone","Boys","Girls","Flag","Dragon","Kiss","Youth","Space","Island","Cream","Punk","Tones","Enemy","Fighters","Birds","Pistols","Mind","Bait","Worms","Fly","Persuasion","Roof","Discovery","Children","School","Theory","Coders","Zebras","Noobs","Crowd","Tail","Nest","Library","Ship","Magic","Question","Error","Rhythm","Babies","Cobwebs","Turn","Aliens","Division","Things","Attraction","Ministers","Ritual","Guns","Night","Winter","Company","Picture","Impulse","Force","Moments","Caress","Skyline","Friday","Abuse","Afternoon","Morning","Evening","Nobodies","Remains","Waters","Party","Martians","Fire","Harvest","Star","911","Route","War","Sky","Roses","Threat","Desert","Head","Brigade","Victim","Generator","Zombies","Church","Dream","Nightmare","Heads","Jam","Horsemen","Symptoms","Emissions","Vengeance","Frustration" };

	return first[rand() % 3] + second[rand() % 163] + "-" + third[rand() % 137];
}

void Generator::generateUsers(std::vector<User>& users, int n)
{
	Timer timer("User generation took:");

	Hash hash;
	User user;

	srand(time(0));
	for (int i = 0; i < n; i++) {
		user.setName(randName());
		user.setBalance(rand() % 999900 + 101);
		user.setPublic_key(hash.toHash(std::to_string(user.getBalance()) + user.getName()));
		users.push_back(user);
	}
}

void Generator::generateTransactions(std::vector<Transaction>& transactions, std::vector<User>& users, int n)
{
	Timer timer("Transaction generation took:");

	Hash hash;
	Transaction transaction;

	srand(time(0));
	for (int i = 0; i < n; i++) {
		transaction.setSender_key(users[rand() % users.size()].getPublic_key());
		transaction.setReceiver_key(users[rand() % users.size()].getPublic_key());
		transaction.setSum(rand() % 1000000 + 1);
		transaction.setTransaction_id(hash.toHash(transaction.getSender_key() + transaction.getReceiver_key() + std::to_string(transaction.getSum())));
		transactions.push_back(transaction);
	}
}