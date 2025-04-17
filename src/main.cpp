#include <iostream>

#include <math.h>
// This is C++20 only
#include <span>
#include <string>
#include <emscripten/bind.h>

int main(int, char**) {
	std::cout << "[3] Hello, C++ 20!" << std::endl;

	std::cout << "Testing span: (expects 2,3,4,5)" << std::endl;
	constexpr int buffer[]{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	std::span slice = { buffer + 2, 4 };
	for (int value : slice) {
		std::cout << " - " << value << std::endl;
	}

	return 0;
}

// 计算两个数字并返回JSON字符串
int calculate(int a, int b) {
    int result = a + b;
    std::cout << "计算结果: " << result << std::endl;
	return result;
}

// using namespace emscripten;

// 计算两个数字并返回JSON字符串
std::string string_cpp_to_js(int a, int b) {
    printf("string_count: %d, %d\n", a, b);
    int result = a + b;
    return "{\"result\": " + std::to_string(result) + "}";
}

// 接收字符串并打印
void string_js_to_cpp(std::string str) {
    printf("C++ 接收来自JavaScript的字符串: %s\n", str.c_str());
}


// 定义计算结果类型
struct Statistic
{
    double commonDPS;   // 普攻dps
    double averageDPS;  // 周期dps
    double skillDPS;    // 技能期dps
    double totalDamage; // 技能总伤
};

Statistic statistic_count(int a, int b) {
	Statistic result;
	result.commonDPS = a + b;
	result.averageDPS = a - b;
	result.skillDPS = a * b;
	result.totalDamage = a / b;
	return result;
}


Statistic cal_hdl(const double atkBuffIn, const double atkBuffExtra,
                  const double atk, const int atkSpeed,
                  const int skill, const double enemyMR,
                  const double mitigaion, const double vulnP,
                  const double vulnR, const double charge)
{
    Statistic result;

    printf("[C++ Log] 调用函数\n");
    printf("[C++ Log] 1 atkBuffIn: %lf\n", atkBuffIn);
    printf("[C++ Log] 2 atkBuffExtra: %lf\n", atkBuffExtra);
    printf("[C++ Log] 3 atk: %lf\n", atk);
    printf("[C++ Log] 4 atkSpeed: %d\n", atkSpeed);
    printf("[C++ Log] 5 skill: %d\n", skill);
    printf("[C++ Log] 6 enemyMR: %lf\n", enemyMR);
    printf("[C++ Log] 7 mitigaion: %lf\n", mitigaion);
    printf("[C++ Log] 8 vulnP: %lf\n", vulnP);
    printf("[C++ Log] 9 vulnR: %lf\n", vulnR);
    printf("[C++ Log] 10 charge: %lf\n", charge);
    double commonDamage = (atk * (1 + atkBuffIn) + atkBuffExtra) * (1 - enemyMR) * (1 - mitigaion); // 普攻dph
    int atkTime = round(3800 / atkSpeed);                                                           // 普攻攻击间隔
    result.commonDPS = commonDamage / atkTime;
    // 根据 skill 的值选择不同的公式
    switch (skill) {
		case 1:
			break;
		case 2:
			break;
		case 3:                                                                          // 三技能
			printf("[C++ Log] 三技能!\n");
			double skillDamage = (atk * (2.9 + atkBuffIn) + atkBuffExtra) * (1 + vulnR); // 技能dph
			int atkSkillTime = round(3000 / atkSpeed);                                   // 技能攻击间隔
			int skillHit = floor(750 / atkSkillTime);                                    // 技能期hit数
			int commonHit = floor(1500 / (atkTime * charge));                            // 普攻hit数
			double chargeTime = round(1500 / charge);                                    // 技能回转

			result.skillDPS = skillDamage * 30 / atkTime;
			result.totalDamage = skillDamage * skillHit;
			result.averageDPS = (commonDamage * commonHit + result.totalDamage) * 30 / (chargeTime + 750);
			break;
    }

    return result;
}

// 使用Emscripten绑定C++函数到JavaScript
EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("calculate", &calculate);
    emscripten::function("string_cpp_to_js", &string_cpp_to_js);
    emscripten::function("string_js_to_cpp", &string_js_to_cpp);
    
    // 绑定Statistic结构体
    emscripten::value_object<Statistic>("Statistic")
        .field("commonDPS", &Statistic::commonDPS)
        .field("averageDPS", &Statistic::averageDPS)
        .field("skillDPS", &Statistic::skillDPS)
        .field("totalDamage", &Statistic::totalDamage);
    
    emscripten::function("statistic_count", &statistic_count);
	emscripten::function("cal_hdl", &cal_hdl);
}