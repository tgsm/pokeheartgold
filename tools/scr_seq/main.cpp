#include <algorithm>
#include <concepts>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using s32 = int32_t;

std::vector<u8> script;

std::size_t cursor = 0;

struct Command {
    std::string name;
    std::vector<int> param_sizes;
};

const std::unordered_map<u16, Command> commands = {
#define C(id, name, ...) {id, {name, {__VA_ARGS__}}}
    C(0, "nop"),
    C(1, "dummy"),
    C(2, "end"),
    C(3, "wait", 2, 2),
    C(4, "loadbyte", 1, 1),
    C(5, "loadword", 1, 4),
    C(6, "loadwordfromaddr", 1, 4),
    C(7, "writebytetoaddr", 4, 1),
    C(8, "setptrbyte", 4, 1),
    C(9, "copylocal", 1, 1),
    C(10, "copybyte", 4, 4),
    C(11, "comparelocaltolocal", 1, 1),
    C(12, "comparelocaltovalue", 1, 1),
    C(13, "comparelocaltoaddr", 1, 4),
    C(14, "compareaddrtolocal", 4, 1),
    C(15, "compareaddrtovalue", 4, 1),
    C(16, "compareaddrtoaddr", 4, 4),
    C(17, "comparevartovalue", 2, 2),
    C(18, "comparevartovar", 2, 2),
    C(19, "runscript", 2),
    C(20, "runscriptwait", 2),
    C(21, "restartcurrentscript"),
    C(22, "goto", 4),
    C(23, "objectgoto", 1, 4),
    C(24, "bggoto", 1, 4),
    C(25, "directiongoto", 1, 4),
    C(26, "call", 4),
    C(27, "return"),
    C(28, "gotoif", 1, 4),
    C(29, "callif", 1, 4),
    C(30, "setflag", 2),
    C(31, "clearflag", 2),
    C(32, "checkflag", 2),
    C(33, "setflagvar", 2),
    C(34, "clearflagvar", 2),
    C(35, "checkflagvar", 2, 2),
    C(36, "settrainerflag", 2),
    C(37, "cleartrainerflag", 2),
    C(38, "checktrainerflag", 2),
    C(39, "addvar", 2, 2),
    C(40, "subvar", 2, 2),
    C(41, "setvar", 2, 2),
    C(42, "copyvar", 2, 2),
    C(43, "setorcopyvar", 2, 2),
    C(44, "message", 1),
    C(45, "scrcmd_045", 1),
    C(46, "scrcmd_046", 2),
    C(47, "scrcmd_047", 2),
    C(48, "scrcmd_048", 1),
    C(49, "scrcmd_049"),
    C(50, "scrcmd_050"),
    C(51, "scrcmd_051"),
    C(52, "scrcmd_052"),
    C(53, "scrcmd_053"),
    C(54, "scrcmd_054"),
    C(55, "scrcmd_055", 1, 1, 2, 2),
    C(56, "scrcmd_056", 1, 2),
    C(57, "scrcmd_057", 1),
    C(58, "scrcmd_058"),
    C(59, "scrcmd_059", 1, 2),
    C(60, "scrcmd_060", 2),
    C(61, "scrcmd_061"),
    C(62, "scrcmd_062", 1, 1, 1, 1, 1, 1),
    C(63, "scrcmd_063", 2),
    C(64, "scrcmd_064", 1, 1, 1, 1, 2),
    C(65, "scrcmd_065", 1, 1, 1, 1, 2),
    C(66, "scrcmd_066", 1, 1),
    C(67, "scrcmd_067"),
    C(68, "scrcmd_068", 1, 1, 1, 1, 2),
    C(69, "scrcmd_069", 1, 1, 1, 1, 2),
    C(70, "scrcmd_070", 2, 2, 2),
    C(71, "scrcmd_071"),
    C(72, "scrcmd_072", 1),
    C(73, "scrcmd_073", 2),
    C(74, "scrcmd_074", 2),
    C(75, "scrcmd_075", 2),
    C(76, "scrcmd_076", 2, 2),
    C(77, "scrcmd_077"),
    C(78, "scrcmd_078", 2),
    C(79, "scrcmd_079"),
    C(80, "scrcmd_080", 2),
    C(81, "scrcmd_081", 2),
    C(82, "scrcmd_082"),
    C(83, "scrcmd_083", 2),
    C(84, "scrcmd_084", 2, 2),
    C(85, "scrcmd_085", 2),
    C(86, "scrcmd_086", 1, 1),
    C(87, "scrcmd_087", 2),
    C(88, "scrcmd_088", 1),
    C(89, "scrcmd_089", 2),
    C(90, "scrcmd_090", 2),
    C(91, "scrcmd_091"),
    C(92, "scrcmd_092"),
    C(93, "scrcmd_093"),
    C(94, "scrcmd_094", 2, 4),
    C(95, "scrcmd_095"),
    C(96, "scrcmd_096"),
    C(97, "scrcmd_097"),
    C(98, "scrcmd_098", 2),
    C(99, "scrcmd_099", 2),
    C(100, "scrcmd_100", 2),
    C(101, "scrcmd_101", 2),
    C(102, "scrcmd_102", 2, 2),
    C(103, "scrcmd_103"),
    C(104, "scrcmd_104"),
    C(105, "scrcmd_105", 2, 2),
    C(106, "scrcmd_106", 2, 2, 2),
    C(107, "scrcmd_107", 2, 2, 2),
    C(108, "scrcmd_108", 2, 1),
    C(109, "scrcmd_109", 2, 2),
    C(110, "scrcmd_110", 4),
    C(111, "scrcmd_111", 4),
    C(112, "scrcmd_112", 2, 4),
    C(113, "scrcmd_113", 2, 2),
    C(114, "scrcmd_114"),
    C(115, "scrcmd_115"),
    C(116, "scrcmd_116", 1),
    C(117, "scrcmd_117"),
    C(118, "scrcmd_118", 1),
    C(119, "scrcmd_119", 2),
    C(120, "scrcmd_120", 2),
    C(121, "scrcmd_121", 2),
    C(122, "scrcmd_122", 2, 2, 2),
    C(123, "scrcmd_123"),
    C(124, "scrcmd_124", 2, 2, 2),
    C(125, "scrcmd_125", 2, 2, 2),
    C(126, "scrcmd_126", 2, 2, 2),
    C(127, "scrcmd_127", 2, 2, 2),
    C(128, "scrcmd_128", 2, 2, 2),
    C(129, "scrcmd_129", 2, 2),
    C(130, "scrcmd_130", 2, 2),
    C(131, "scrcmd_131", 2),
    C(132, "scrcmd_132", 1, 1),
    C(133, "scrcmd_133", 2, 2),
    C(134, "scrcmd_134", 2, 2),
    C(135, "scrcmd_135", 2, 2, 2),
    C(136, "scrcmd_136", 2, 2),
    C(137, "scrcmd_137", 2, 2, 2, 2, 2, 2),
    C(138, "scrcmd_138", 2, 2),
    C(139, "scrcmd_139", 2, 2, 2),
    C(140, "scrcmd_140", 2, 2, 2),
    C(141, "scrcmd_141", 2, 2),
    C(142, "scrcmd_142", 2, 2),
    C(143, "scrcmd_143", 2, 2, 2),
    C(144, "scrcmd_144", 2),
    C(145, "scrcmd_145", 1),
    C(146, "scrcmd_146", 2),
    C(147, "scrcmd_147", 2, 2),
    C(148, "scrcmd_148", 2, 2),
    C(149, "scrcmd_149", 1),
    C(150, "scrcmd_150"),
    C(151, "scrcmd_151"),
    C(152, "scrcmd_152"),
    C(153, "scrcmd_153", 2, 2, 2),
    C(154, "scrcmd_154", 2, 2, 2),
    C(155, "scrcmd_155", 2, 2),
    C(156, "scrcmd_156"),
    C(157, "scrcmd_157"),
    C(158, "scrcmd_158", 1),
    C(159, "scrcmd_159"),
    C(160, "scrcmd_160"),
    C(161, "scrcmd_161"),
    C(162, "scrcmd_162"),
    C(163, "scrcmd_163", 2),
    C(164, "scrcmd_164", 2, 2, 2, 2),
    C(165, "scrcmd_165", 2, 2),
    C(166, "scrcmd_166", 2),
    C(167, "scrcmd_167"),
    C(168, "scrcmd_168", 2),
    C(169, "scrcmd_169", 2, 2),
    C(170, "scrcmd_170", 2),
    C(171, "scrcmd_171", 2, 2),
    C(172, "scrcmd_172"),
    C(173, "scrcmd_173", 2, 2),
    C(174, "scrcmd_174", 2, 2, 2, 2),
    C(175, "scrcmd_175"),
    C(176, "scrcmd_176", 2, 2, 2, 2, 2),
    C(177, "scrcmd_177", 2),
    C(178, "scrcmd_178", 2, 2, 2, 2),
    C(179, "scrcmd_179", 2),
    C(180, "scrcmd_180"),
    C(181, "scrcmd_181"),
    C(182, "scrcmd_182", 2),
    C(183, "scrcmd_183", 2),
    C(184, "scrcmd_184", 2),
    C(185, "scrcmd_185", 1),
    C(186, "scrcmd_186", 1),
    C(187, "scrcmd_187", 2),
    C(188, "scrcmd_188", 2),
    C(189, "scrcmd_189"),
    C(190, "scrcmd_190", 1),
    C(191, "scrcmd_191", 1),
    C(192, "scrcmd_192", 1),
    C(193, "scrcmd_193", 1, 2),
    C(194, "scrcmd_194", 1, 2),
    C(195, "scrcmd_195", 1, 2),
    C(196, "scrcmd_196", 1, 2),
    C(197, "scrcmd_197", 1, 2),
    C(198, "scrcmd_198", 1, 2),
    C(199, "scrcmd_199", 1, 2),
    C(200, "scrcmd_200", 1, 2),
    C(201, "scrcmd_201", 1),
    C(202, "scrcmd_202", 1, 2, 2, 1),
    C(203, "scrcmd_203", 1),
    C(204, "scrcmd_204", 1),
    C(205, "scrcmd_205", 1),
    C(206, "scrcmd_206", 2),
    C(207, "scrcmd_207", 1),
    C(208, "scrcmd_208", 1, 2),
    C(209, "scrcmd_209", 1, 2),
    C(210, "scrcmd_210", 1, 2),
    C(211, "scrcmd_211", 1, 2),
    C(212, "scrcmd_212", 2),
    C(213, "scrcmd_213", 2, 2, 1, 1),
    C(214, "scrcmd_214", 2, 2),
    C(215, "scrcmd_215", 2, 2, 2),
    C(216, "scrcmd_216", 2, 2, 2),
    C(217, "scrcmd_217", 2),
    C(218, "scrcmd_218", 2),
    C(219, "scrcmd_219"),
    C(220, "scrcmd_220", 2),
    C(221, "scrcmd_221", 2, 1),
    C(222, "scrcmd_222", 2),
    C(223, "scrcmd_223", 1, 2),
    C(224, "scrcmd_224", 1, 2),
    C(225, "scrcmd_225", 1, 2),
    C(226, "scrcmd_226", 2, 2, 2, 2),
    C(227, "scrcmd_227", 2, 2, 2, 2),
    C(228, "scrcmd_228", 2),
    C(229, "scrcmd_229", 2, 2),
    C(230, "scrcmd_230"),
    C(231, "scrcmd_231", 2, 2, 2),
    C(232, "scrcmd_232", 2, 2, 2),
    C(233, "scrcmd_233", 2),
    C(234, "scrcmd_234", 2, 2, 2, 2),
    C(235, "scrcmd_235", 2),
    C(236, "scrcmd_236", 2, 2, 2, 2, 2),
    C(237, "scrcmd_237"),
    C(238, "scrcmd_238", 2, 2, 2, 2),
    C(239, "scrcmd_239", 2, 2),
    C(240, "scrcmd_240", 2, 2, 2, 2, 2),
    C(241, "scrcmd_241", 2),
    C(242, "scrcmd_242", 1, 1, 2, 2),
    C(243, "scrcmd_243", 2),
    C(244, "scrcmd_244", 2),
    C(245, "scrcmd_245", 2),
    C(246, "scrcmd_246", 2),
    C(247, "scrcmd_247"),
    C(248, "scrcmd_248", 2),
    C(249, "scrcmd_249", 2, 2),
    C(250, "scrcmd_250", 2, 2),
    C(251, "scrcmd_251"),
    C(252, "scrcmd_252"),
    C(253, "scrcmd_253", 2),
    C(254, "scrcmd_254", 2),
    C(255, "scrcmd_255", 2, 2),
    C(256, "scrcmd_256", 2),
    C(257, "scrcmd_257", 2),
    C(258, "scrcmd_258", 2, 2),
    C(259, "scrcmd_259", 1, 1),
    C(260, "scrcmd_260", 2),
    C(261, "scrcmd_261", 2),
    C(262, "scrcmd_262"),
    C(263, "scrcmd_263"),
    C(264, "scrcmd_264", 2),
    C(265, "scrcmd_265"),
    C(266, "scrcmd_266"),
    C(267, "scrcmd_267", 2, 2),
    C(268, "scrcmd_268", 2),
    C(269, "scrcmd_269", 2, 2, 2, 2),
    C(270, "scrcmd_270", 2),
    C(271, "scrcmd_271", 2, 2),
    C(272, "scrcmd_272", 2),
    C(273, "scrcmd_273", 2),
    C(274, "scrcmd_274", 2, 2),
    C(275, "scrcmd_275", 2),
    C(276, "scrcmd_276", 2),
    C(277, "scrcmd_277", 2),
    C(278, "scrcmd_278", 2, 2, 2, 2),
    C(279, "scrcmd_279"),
    C(280, "scrcmd_280"),
    C(281, "scrcmd_281", 2),
    C(282, "scrcmd_282"),
    C(283, "scrcmd_283"),
    C(284, "scrcmd_284"),
    C(285, "scrcmd_285", 2, 2),
    C(286, "scrcmd_286", 2),
    C(287, "scrcmd_287", 2, 2),
    C(288, "scrcmd_288", 2, 2),
    C(289, "scrcmd_289", 2),
    C(290, "scrcmd_290", 2, 2),
    C(291, "scrcmd_291"),
    C(292, "scrcmd_292"),
    C(293, "scrcmd_293"),
    C(294, "scrcmd_294", 2, 2),
    C(295, "scrcmd_295", 2),
    C(296, "scrcmd_296", 2),
    C(297, "scrcmd_297"),
    C(298, "scrcmd_298", 2, 2, 2, 2),
    C(299, "scrcmd_299", 2),
    C(300, "scrcmd_300", 2),
    C(301, "scrcmd_301", 2),
    C(302, "scrcmd_302", 2, 2),
    C(303, "scrcmd_303", 2, 2),
    C(304, "scrcmd_304", 2),
    C(305, "scrcmd_305"),
    C(306, "scrcmd_306", 2, 2, 2, 2),
    C(307, "scrcmd_307", 2, 2, 2, 2, 1),
    C(308, "scrcmd_308", 1),
    C(309, "scrcmd_309", 1),
    C(310, "scrcmd_310", 1),
    C(311, "scrcmd_311", 1),
    C(312, "scrcmd_312"),
    C(313, "scrcmd_313", 2),
    C(314, "scrcmd_314"),
    C(315, "scrcmd_315"),
    C(316, "scrcmd_316"),
    C(317, "scrcmd_317", 1),
    C(318, "scrcmd_318"),
    C(319, "scrcmd_319", 2),
    C(320, "scrcmd_320", 2),
    C(321, "scrcmd_321", 2),
    C(322, "scrcmd_322", 1, 2),
    C(323, "scrcmd_323", 2, 2),
    C(324, "scrcmd_324"),
    C(325, "scrcmd_325"),
    C(326, "scrcmd_326"),
    C(327, "scrcmd_327", 1),
    C(328, "scrcmd_328", 1),
    C(329, "scrcmd_329"),
    C(330, "scrcmd_330"),
    C(331, "scrcmd_331"),
    C(332, "scrcmd_332", 2),
    C(333, "scrcmd_333", 2),
    C(334, "scrcmd_334"),
    C(335, "scrcmd_335"),
    C(336, "scrcmd_336"),
    C(337, "scrcmd_337"),
    C(338, "scrcmd_338", 2, 2, 2),
    C(339, "scrcmd_339", 2, 2, 2, 2, 2),
    C(340, "scrcmd_340", 2, 2),
    C(341, "scrcmd_341", 2, 2),
    C(342, "scrcmd_342", 2, 2, 2),
    C(343, "scrcmd_343"),
    C(344, "scrcmd_344", 2, 2),
    C(345, "scrcmd_345"),
    C(346, "scrcmd_346"),
    C(347, "scrcmd_347", 2, 2),
    C(348, "scrcmd_348", 2),
    C(349, "scrcmd_349"),
    C(350, "scrcmd_350"),
    C(351, "scrcmd_351", 2),
    C(352, "scrcmd_352", 1, 2, 2),
    C(353, "scrcmd_353", 1, 2),
    C(354, "scrcmd_354", 2, 2),
    C(355, "scrcmd_355", 2, 2),
    C(356, "scrcmd_356", 2),
    C(357, "scrcmd_357", 2, 2),
    C(358, "scrcmd_358", 2),
    C(359, "scrcmd_359", 2),
    C(360, "scrcmd_360", 2),
    C(361, "scrcmd_361", 2, 2),
    C(362, "scrcmd_362", 2, 2),
    C(363, "scrcmd_363", 1, 2, 2),
    C(364, "scrcmd_364", 2),
    C(365, "scrcmd_365"),
    C(366, "scrcmd_366"),
    C(367, "scrcmd_367", 2, 2),
    C(368, "scrcmd_368", 2, 2),
    C(369, "scrcmd_369"),
    C(370, "scrcmd_370"),
    C(371, "scrcmd_371", 2, 2),
    C(372, "scrcmd_372", 2, 2),
    C(373, "scrcmd_373", 2),
    C(374, "scrcmd_374", 2),
    C(375, "scrcmd_375", 2),
    C(376, "scrcmd_376"),
    C(377, "scrcmd_377", 2),
    C(378, "scrcmd_378", 2, 2),
    C(379, "scrcmd_379", 2),
    C(380, "scrcmd_380", 2, 2),
    C(381, "scrcmd_381", 2),
    C(382, "scrcmd_382", 2, 2),
    C(383, "scrcmd_383", 2, 2),
    C(384, "scrcmd_384", 1),
    C(385, "scrcmd_385", 2, 2),
    C(386, "scrcmd_386", 2),
    C(387, "scrcmd_387", 2),
    C(388, "scrcmd_388", 2),
    C(389, "scrcmd_389", 2),
    C(390, "scrcmd_390", 2, 2),
    C(391, "scrcmd_391", 2),
    C(392, "scrcmd_392", 2, 2, 2),
    C(393, "scrcmd_393", 2, 2, 2),
    C(394, "scrcmd_394", 2),
    C(395, "scrcmd_395", 2),
    C(396, "scrcmd_396", 2, 2),
    C(397, "scrcmd_397", 2, 2),
    C(398, "scrcmd_398", 2, 2, 2),
    C(399, "scrcmd_399", 1, 2, 2),
    C(400, "scrcmd_400?"),
    C(401, "scrcmd_401?"),
    C(402, "scrcmd_402?"),
    C(403, "scrcmd_403", 2, 2),
    C(404, "scrcmd_404", 2, 2, 2),
    C(405, "scrcmd_405", 2, 2),
    C(406, "scrcmd_406", 2),
    C(407, "scrcmd_407", 2, 2),
    C(408, "scrcmd_408", 2, 2),
    C(409, "scrcmd_409"),
    C(410, "scrcmd_410", 2, 2),
    C(411, "scrcmd_411"),
    C(412, "scrcmd_412", 2, 2, 2),
    C(413, "scrcmd_413", 2, 2, 2, 2),
    C(414, "scrcmd_414", 2),
    C(415, "scrcmd_415", 2),
    C(416, "scrcmd_416", 2, 2, 2),
    C(417, "scrcmd_417", 2, 2),
    C(418, "scrcmd_418", 2, 2),
    C(419, "scrcmd_419", 2, 2, 2),
    C(420, "scrcmd_420", 2),
    C(421, "scrcmd_421"),
    C(422, "scrcmd_422"),
    C(423, "scrcmd_423", 2),
    C(424, "scrcmd_424", 2),
    C(425, "scrcmd_425", 2),
    C(426, "scrcmd_426", 1, 2, 2),
    C(427, "scrcmd_427", 2, 2),
    C(428, "scrcmd_428", 2),
    C(429, "scrcmd_429", 2),
    C(430, "scrcmd_430", 2, 2, 2),
    C(431, "scrcmd_431", 2, 2, 2),
    C(432, "scrcmd_432", 2, 2),
    C(433, "scrcmd_433", 2, 2, 2),
    C(434, "scrcmd_434", 2, 2),
    C(435, "scrcmd_435", 2, 2),
    C(436, "scrcmd_436"),
    C(437, "scrcmd_437", 2),
    C(438, "scrcmd_438", 2, 2),
    C(439, "scrcmd_439", 2, 2),
    C(440, "scrcmd_440", 2, 2),
    C(441, "scrcmd_441", 2, 2),
    C(442, "scrcmd_442", 2, 2),
    C(443, "scrcmd_443"),
    C(444, "scrcmd_444", 2, 2),
    C(445, "scrcmd_445", 2),
    C(446, "scrcmd_446", 2),
    C(447, "scrcmd_447", 2),
    C(448, "scrcmd_448", 2, 2, 2, 2, 2),
    C(449, "scrcmd_449", 2, 2),
    C(450, "scrcmd_450", 2),
    C(451, "scrcmd_451", 2),
    C(452, "scrcmd_452", 2, 2),
    C(453, "scrcmd_453"),
    C(454, "scrcmd_454"),
    C(455, "scrcmd_455", 2),
    C(456, "scrcmd_456", 2, 2),
    C(457, "scrcmd_457", 2, 2),
    C(458, "scrcmd_458", 2, 2, 2),
    C(459, "scrcmd_459"),
    C(460, "scrcmd_460", 2, 2),
    C(461, "scrcmd_461", 1, 2, 2),
    C(462, "scrcmd_462", 2),
    C(463, "scrcmd_463"),
    C(464, "scrcmd_464", 1),
    C(465, "scrcmd_465", 2, 2, 2),
    C(466, "scrcmd_466", 2, 2),
    C(467, "scrcmd_467", 2),
    C(468, "scrcmd_468", 2, 2),
    C(469, "scrcmd_469", 2),
    C(470, "scrcmd_470", 1),
    C(471, "scrcmd_471"),
    C(472, "scrcmd_472", 2),
    C(473, "scrcmd_473", 2),
    C(474, "scrcmd_474"),
    C(475, "scrcmd_475", 2, 2),
    C(476, "scrcmd_476"),
    C(477, "scrcmd_477", 1, 2),
    C(478, "scrcmd_478", 2, 2, 2, 2),
    C(479, "scrcmd_479"),
    C(480, "scrcmd_480", 2, 2, 2),
    C(481, "scrcmd_481", 2, 2),
    C(482, "scrcmd_482", 2, 2),
    C(483, "scrcmd_483", 2, 2),
    C(484, "scrcmd_484", 2),
    C(485, "scrcmd_485", 2),
    C(486, "scrcmd_486"),
    C(487, "scrcmd_487", 2),
    C(488, "scrcmd_488", 2, 2),
    C(489, "scrcmd_489?"),
    C(490, "scrcmd_490", 2),
    C(491, "scrcmd_491", 2),
    C(492, "scrcmd_492", 2, 2, 2),
    C(493, "scrcmd_493", 2, 2, 2),
    C(494, "scrcmd_494", 2, 2),
    C(495, "scrcmd_495", 2),
    C(496, "scrcmd_496"),
    C(497, "scrcmd_497", 2, 2, 2),
    C(498, "scrcmd_498", 2, 2, 2, 2, 2),
    C(499, "scrcmd_499", 2, 2, 2, 2, 2),
    C(500, "scrcmd_500", 1),
    C(501, "scrcmd_501", 1),
    C(502, "scrcmd_502", 2, 2),
    C(503, "scrcmd_503", 2),
    C(504, "scrcmd_504", 2, 2, 2, 2),
    C(505, "scrcmd_505"),
    C(506, "scrcmd_506", 1, 2),
    C(507, "scrcmd_507", 2),
    C(508, "scrcmd_508", 2),
    C(509, "scrcmd_509", 2),
    C(510, "scrcmd_510"),
    C(511, "scrcmd_511", 2, 2),
    C(512, "scrcmd_512", 2),
    C(513, "scrcmd_513", 2, 2, 2),
    C(514, "scrcmd_514", 2),
    C(515, "scrcmd_515", 2),
    C(516, "scrcmd_516", 1, 2),
    C(517, "scrcmd_517", 2, 2),
    C(518, "scrcmd_518", 2),
    C(519, "scrcmd_519", 1, 2),
    C(520, "scrcmd_520"),
    C(521, "scrcmd_521"),
    C(522, "scrcmd_522", 2),
    C(523, "scrcmd_523", 2, 2, 2, 2, 2),
    C(524, "scrcmd_524", 2, 2, 2, 2, 2),
    C(525, "scrcmd_525", 2),
    C(526, "scrcmd_526"),
    C(527, "scrcmd_527", 2),
    C(528, "scrcmd_528", 2),
    C(529, "scrcmd_529", 2),
    C(530, "scrcmd_530", 2, 1),
    C(531, "scrcmd_531", 1, 2),
    C(532, "scrcmd_532", 2, 2, 2),
    C(533, "scrcmd_533", 2, 2, 2),
    C(534, "scrcmd_534", 2),
    C(535, "scrcmd_535", 2, 2),
    C(536, "scrcmd_536", 2),
    C(537, "scrcmd_537"),
    C(538, "scrcmd_538", 2, 2),
    C(539, "scrcmd_539"),
    C(540, "scrcmd_540", 2),
    C(541, "scrcmd_541", 1, 2, 1, 1),
    C(542, "scrcmd_542"),
    C(543, "scrcmd_543", 2),
    C(544, "scrcmd_544", 2, 2),
    C(545, "scrcmd_545", 2),
    C(546, "scrcmd_546", 1, 2),
    C(547, "scrcmd_547", 2),
    C(548, "scrcmd_548"),
    C(549, "scrcmd_549", 2),
    C(550, "scrcmd_550", 1),
    C(551, "scrcmd_551", 2),
    C(552, "scrcmd_552", 2, 2),
    C(553, "scrcmd_553", 1, 2),
    C(554, "scrcmd_554"),
    C(555, "scrcmd_555", 2),
    C(556, "scrcmd_556", 2),
    C(557, "scrcmd_557", 2, 2),
    C(558, "scrcmd_558", 2, 2),
    C(559, "scrcmd_559", 2),
    C(560, "scrcmd_560", 2, 2),
    C(561, "scrcmd_561", 2, 2, 2, 2),
    C(562, "scrcmd_562", 2, 2, 2, 1),
    C(563, "scrcmd_563", 2, 2),
    C(564, "scrcmd_564", 2),
    C(565, "scrcmd_565", 2),
    C(566, "scrcmd_566"),
    C(567, "scrcmd_567", 2, 2, 2, 2),
    C(568, "scrcmd_568", 2, 2),
    C(569, "scrcmd_569", 2),
    C(570, "scrcmd_570", 2, 2, 2),
    C(571, "scrcmd_571", 2),
    C(572, "scrcmd_572", 2),
    C(573, "scrcmd_573"),
    C(574, "scrcmd_574", 2, 2),
    C(575, "scrcmd_575"),
    C(576, "scrcmd_576", 2),
    C(577, "scrcmd_577"),
    C(578, "scrcmd_578"),
    C(579, "scrcmd_579"),
    C(580, "scrcmd_580", 1, 2),
    C(581, "scrcmd_581", 2, 2),
    C(582, "scrcmd_582", 2, 2, 2),
    C(583, "scrcmd_583", 2),
    C(584, "scrcmd_584", 2),
    C(585, "scrcmd_585"),
    C(586, "scrcmd_586", 2),
    C(587, "scrcmd_587"),
    C(588, "scrcmd_588", 2),
    C(589, "scrcmd_589", 2, 2, 1),
    C(590, "scrcmd_590", 2),
    C(591, "scrcmd_591"),
    C(592, "scrcmd_592", 2),
    C(593, "scrcmd_593"),
    C(594, "scrcmd_594"),
    C(595, "scrcmd_595", 1),
    C(596, "scrcmd_596", 2),
    C(597, "scrcmd_597"),
    C(598, "scrcmd_598", 2),
    C(599, "scrcmd_599"),
    C(600, "scrcmd_600"),
    C(601, "scrcmd_601"),
    C(602, "scrcmd_602", 2),
    C(603, "scrcmd_603"),
    C(604, "scrcmd_604", 2),
    C(605, "scrcmd_605", 1, 1),
    C(606, "scrcmd_606"),
    C(607, "scrcmd_607"),
    C(608, "scrcmd_608"),
    C(609, "scrcmd_609"),
    C(610, "scrcmd_610"),
    C(611, "scrcmd_611", 2, 2, 2, 2, 2, 2),
    C(612, "scrcmd_612", 2),
    C(613, "scrcmd_613", 2),
    C(614, "scrcmd_614", 2),
    C(615, "scrcmd_615", 2, 2),
    C(616, "scrcmd_616", 2),
    C(617, "scrcmd_617", 2, 2),
    C(618, "scrcmd_618", 2),
    C(619, "scrcmd_619", 2),
    C(620, "scrcmd_620", 1),
    C(621, "scrcmd_621", 2),
    C(622, "scrcmd_622", 2, 2),
    C(623, "scrcmd_623", 2),
    C(624, "scrcmd_624", 2),
    C(625, "scrcmd_625", 2, 2, 2),
    C(626, "scrcmd_626", 1, 2),
    C(627, "scrcmd_627", 1),
    C(628, "scrcmd_628", 2, 2),
    C(629, "scrcmd_629", 2),
    C(630, "scrcmd_630", 2, 2, 2),
    C(631, "scrcmd_631", 2, 2, 2),
    C(632, "scrcmd_632", 2, 2),
    C(633, "scrcmd_633", 2, 2, 2),
    C(634, "scrcmd_634", 2, 2),
    C(635, "scrcmd_635", 2, 2),
    C(636, "scrcmd_636", 2),
    C(637, "scrcmd_637", 2, 2, 2),
    C(638, "scrcmd_638", 2, 2, 2),
    C(639, "scrcmd_639", 2, 2, 2),
    C(640, "scrcmd_640", 2, 2, 2),
    C(641, "scrcmd_641", 2, 2, 2),
    C(642, "scrcmd_642", 2, 2, 2),
    C(643, "scrcmd_643", 2, 2, 2),
    C(644, "scrcmd_644", 2, 2, 2),
    C(645, "scrcmd_645", 2, 2, 2),
    C(646, "scrcmd_646", 2),
    C(647, "scrcmd_647", 2),
    C(648, "scrcmd_648", 2),
    C(649, "scrcmd_649"),
    C(650, "scrcmd_650", 2),
    C(651, "scrcmd_651", 2, 2, 2),
    C(652, "scrcmd_652", 2, 2, 2),
    C(653, "scrcmd_653", 2, 2, 2, 2),
    C(654, "scrcmd_654", 2, 2, 2),
    C(655, "scrcmd_655", 2, 2),
    C(656, "scrcmd_656", 2, 2),
    C(657, "scrcmd_657", 2, 2, 2, 2),
    C(658, "scrcmd_658", 1, 2),
    C(659, "scrcmd_659", 2),
    C(660, "scrcmd_660", 2),
    C(661, "scrcmd_661"),
    C(662, "scrcmd_662", 2, 2, 2),
    C(663, "scrcmd_663", 2),
    C(664, "scrcmd_664"),
    C(665, "scrcmd_665", 2),
    C(666, "scrcmd_666", 2, 2),
    C(667, "scrcmd_667", 2, 2, 2, 2),
    C(668, "scrcmd_668", 1, 2),
    C(669, "scrcmd_669", 2, 2),
    C(670, "scrcmd_670", 2, 2),
    C(671, "scrcmd_671"),
    C(672, "scrcmd_672", 2, 2, 2),
    C(673, "scrcmd_673", 2, 2, 2, 2, 2),
    C(674, "scrcmd_674", 2, 2),
    C(675, "scrcmd_675", 2, 2, 2, 2),
    C(676, "scrcmd_676", 2, 2),
    C(677, "scrcmd_677"),
    C(678, "scrcmd_678", 2, 2, 2),
    C(679, "scrcmd_679", 2, 2),
    C(680, "scrcmd_680", 2, 2),
    C(681, "scrcmd_681", 2),
    C(682, "scrcmd_682", 2),
    C(683, "scrcmd_683", 2),
    C(684, "scrcmd_684"),
    C(685, "scrcmd_685", 2, 2),
    C(686, "scrcmd_686"),
    C(687, "scrcmd_687", 2),
    C(688, "scrcmd_688", 2),
    C(689, "scrcmd_689", 2),
    C(690, "scrcmd_690", 2, 2),
    C(691, "scrcmd_691", 2),
    C(692, "scrcmd_692"),
    C(693, "scrcmd_693", 2),
    C(694, "scrcmd_694", 2),
    C(695, "scrcmd_695", 2),
    C(696, "scrcmd_696", 2),
    C(697, "scrcmd_697"),
    C(698, "scrcmd_698", 1, 2, 2),
    C(699, "scrcmd_699"),
    C(700, "scrcmd_700", 2),
    C(701, "scrcmd_701", 2, 2, 2, 2),
    C(702, "scrcmd_702"),
    C(703, "scrcmd_703"),
    C(704, "scrcmd_704", 2),
    C(705, "scrcmd_705"),
    C(706, "scrcmd_706", 2),
    C(707, "scrcmd_707", 2, 2),
    C(708, "scrcmd_708", 2),
    C(709, "scrcmd_709"),
    C(710, "scrcmd_710"),
    C(711, "scrcmd_711"),
    C(712, "scrcmd_712", 1),
    C(713, "scrcmd_713", 1),
    C(714, "scrcmd_714", 1),
    C(715, "scrcmd_715"),
    C(716, "scrcmd_716"),
    C(717, "scrcmd_717", 2),
    C(718, "scrcmd_718", 1, 2),
    C(719, "scrcmd_719", 2, 2),
    C(720, "scrcmd_720", 2),
    C(721, "scrcmd_721", 2),
    C(722, "scrcmd_722", 1, 1, 2, 2, 2),
    C(723, "scrcmd_723", 2, 2, 2),
    C(724, "scrcmd_724", 2, 2),
    C(725, "scrcmd_725", 1, 2),
    C(726, "scrcmd_726"),
    C(727, "scrcmd_727", 2),
    C(728, "scrcmd_728", 1, 1),
    C(729, "scrcmd_729", 2),
    C(730, "scrcmd_730", 2),
    C(731, "scrcmd_731"),
    C(732, "scrcmd_732", 1),
    C(733, "scrcmd_733", 1, 2),
    C(734, "scrcmd_734", 1),
    C(735, "scrcmd_735", 2),
    C(736, "scrcmd_736"),
    C(737, "scrcmd_737", 2),
    C(738, "scrcmd_738", 2),
    C(739, "scrcmd_739"),
    C(740, "scrcmd_740", 2, 2, 2),
    C(741, "scrcmd_741", 2, 2, 2, 2),
    C(742, "scrcmd_742", 2, 2, 2),
    C(743, "scrcmd_743", 2),
    C(744, "scrcmd_744"),
    C(745, "scrcmd_745", 1, 2),
    C(746, "scrcmd_746"),
    C(747, "scrcmd_747"),
    C(748, "scrcmd_748", 2),
    C(749, "scrcmd_749", 1, 1, 1, 1, 2),
    C(750, "scrcmd_750", 1, 1, 1, 1, 2),
    C(751, "scrcmd_751", 2, 2, 2),
    C(752, "scrcmd_752"),
    C(753, "scrcmd_753", 2, 2, 2),
    C(754, "scrcmd_754", 2),
    C(755, "scrcmd_755"),
    C(756, "scrcmd_756"),
    C(757, "scrcmd_757", 2, 2),
    C(758, "scrcmd_758", 2, 2, 2),
    C(759, "scrcmd_759"),
    C(760, "scrcmd_760"),
    C(761, "scrcmd_761", 2),
    C(762, "scrcmd_762", 2),
    C(763, "scrcmd_763"),
    C(764, "scrcmd_764"),
    C(765, "scrcmd_765"),
    C(766, "scrcmd_766", 2, 2),
    C(767, "scrcmd_767", 2, 2),
    C(768, "scrcmd_768"),
    C(769, "scrcmd_769"),
    C(770, "scrcmd_770", 2),
    C(771, "scrcmd_771"),
    C(772, "scrcmd_772", 2, 2, 2, 2),
    C(773, "scrcmd_773", 2),
    C(774, "scrcmd_774", 2, 2),
    C(775, "scrcmd_775", 2, 2),
    C(776, "scrcmd_776"),
    C(777, "scrcmd_777", 2, 2),
    C(778, "scrcmd_778"),
    C(779, "scrcmd_779", 2, 2),
    C(780, "scrcmd_780", 2),
    C(781, "scrcmd_781", 2),
    C(782, "scrcmd_782"),
    C(783, "scrcmd_783", 1),
    C(784, "scrcmd_784", 2),
    C(785, "scrcmd_785", 2, 1),
    C(786, "scrcmd_786", 1),
    C(787, "scrcmd_787", 2, 2, 2),
    C(788, "scrcmd_788", 1, 2),
    C(789, "scrcmd_789", 1),
    C(790, "scrcmd_790", 2, 2),
    C(791, "scrcmd_791", 2, 2, 2),
    C(792, "scrcmd_792", 2, 2),
    C(793, "scrcmd_793", 2, 2),
    C(794, "scrcmd_794", 2, 2, 2),
    C(795, "scrcmd_795", 2, 2),
    C(796, "scrcmd_796"),
    C(797, "scrcmd_797", 2),
    C(798, "scrcmd_798", 2),
    C(799, "scrcmd_799", 2),
    C(800, "scrcmd_800", 2),
    C(801, "scrcmd_801", 2),
    C(802, "scrcmd_802"),
    C(803, "scrcmd_803", 2, 2),
    C(804, "scrcmd_804", 1),
    C(805, "scrcmd_805"),
    C(806, "scrcmd_806"),
    C(807, "scrcmd_807", 2, 2),
    C(808, "scrcmd_808", 2),
    C(809, "scrcmd_809", 2),
    C(810, "scrcmd_810"),
    C(811, "scrcmd_811", 2, 2),
    C(812, "scrcmd_812", 2, 2, 2, 2),
    C(813, "scrcmd_813", 2),
    C(814, "scrcmd_814"),
    C(815, "scrcmd_815", 2),
    C(816, "scrcmd_816"),
    C(817, "scrcmd_817", 1),
    C(818, "scrcmd_818"),
    C(819, "scrcmd_819", 2),
    C(820, "scrcmd_820", 1),
    C(821, "scrcmd_821", 2, 2),
    C(822, "scrcmd_822", 2),
    C(823, "scrcmd_823", 2),
    C(824, "scrcmd_824", 2),
    C(825, "scrcmd_825", 2, 2),
    C(826, "scrcmd_826", 2),
    C(827, "scrcmd_827", 2, 2),
    C(828, "scrcmd_828", 2, 2, 1),
    C(829, "scrcmd_829", 2),
    C(830, "scrcmd_830", 2),
    C(831, "scrcmd_831", 2),
    C(832, "scrcmd_832", 2),
    C(833, "scrcmd_833", 2),
    C(834, "scrcmd_834", 2),
    C(835, "scrcmd_835", 2),
    C(836, "scrcmd_836", 2),
    C(837, "scrcmd_837", 2),
    C(838, "scrcmd_838", 2, 2),
    C(839, "scrcmd_839", 2),
    C(840, "scrcmd_840", 2, 2),
    C(841, "scrcmd_841", 1),
    C(842, "scrcmd_842", 1),
    C(843, "scrcmd_843", 1, 2),
    C(844, "scrcmd_844", 1, 2),
    C(845, "scrcmd_845", 1, 2),
    C(846, "scrcmd_846", 2, 2, 2),
    C(847, "scrcmd_847", 1),
    C(848, "scrcmd_848", 1, 2),
    C(849, "scrcmd_849", 1, 2),
    C(850, "scrcmd_850", 1, 2),
    C(851, "scrcmd_851", 1),
    C(852, "scrcmd_852", 1, 1),
#undef C
};

std::vector<std::size_t> script_offsets;
std::vector<std::size_t> function_offsets;

template <typename T>
inline bool Contains(std::vector<T>& vec, T value) {
    return std::ranges::find(vec, value) != vec.end();
}

template <typename T>
std::vector<T> RemoveDuplicates(std::vector<T>& vec) {
    std::vector<T> unique_elements;

    for (T i : vec) {
        if (!Contains(unique_elements, i)) {
            unique_elements.push_back(i);
        }
    }

    return unique_elements;
}

template <std::integral T>
T Read() {
    T value = 0;
    for (std::size_t i = 0; i < sizeof(T); i++) {
        value |= script.at(cursor + i) << (i * 8);
    }

    cursor += sizeof(T);

    return value;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("need filename\n");
        return 1;
    }

    const std::filesystem::path& script_path = argv[1];
    std::ifstream stream(script_path, std::ios::binary);
    if (!stream.is_open()) {
        printf("could not open file\n");
        return 1;
    }

    const std::size_t script_file_size = std::filesystem::file_size(script_path);

    script.resize(script_file_size);
    stream.read(reinterpret_cast<char*>(script.data()), script_file_size);

    while (true) {
        u16 checker = Read<u16>();
        cursor -= sizeof(u16);

        u32 offset = Read<u32>();

        if (offset == 0) {
            break;
        }

        if (checker == 0xFD13) {
            break;
        }

        script_offsets.push_back(offset + cursor);
    }

    printf("\t.text\n");
    printf("\t.include \"asm/macros/script.inc\"\n\n");

    printf("_offsets:\n");
    for (size_t offset : script_offsets) {
        printf("\t.word 0x%08lX\n", offset);
    }
    printf("\tscrdef_end\n\n");

    cursor -= 2;
    u32 script_counter = 0;
    while (true) {
        try {
            if (Contains(script_offsets, cursor)) {
                printf("_scr%03u:\n", script_counter++);
            }

            u16 command_id = Read<u16>();

            printf("\t%s", commands.at(command_id).name.c_str());

            const auto& param_sizes = commands.at(command_id).param_sizes;
            for (size_t i = 0; i < param_sizes.size(); i++) {
                switch (param_sizes.at(i)) {
                    case sizeof(u8):
                        printf(" 0x%02X", Read<u8>());
                        break;
                    case sizeof(u16):
                        printf(" 0x%04X", Read<u16>());
                        break;
                    case sizeof(u32): {
                        s32 value = Read<s32>();
                        switch (command_id) {
                            case 22:
                            case 26:
                            case 28:
                            case 29:
                                function_offsets.push_back(cursor + value);
                                break;
                        }
                        printf(" 0x%08X", value);
                    }
                        break;
                    default:
                        printf("bad param length\n");
                        std::exit(1);
                }

                if (i != param_sizes.size() - 1) {
                    printf(",");
                }
            }

            printf("\n");
            
            if (command_id == 0x0002 || command_id == 0x0016) {
                printf("\n");
                continue;
            }
        } catch (std::out_of_range& e) {
            printf("EOF\n");
            std::exit(0);
        }
    }

    // const size_t initial_size = function_offsets.size();
    // for (int iter = 0; iter < 30; iter++) {
    //     std::ranges::sort(function_offsets);

    //     for (size_t i = 0; i < initial_size; i++) {
    //         cursor = function_offsets.at(i);

    //         while (true) {
    //             u16 command_id = Read<u16>();

    //             // printf("    %s", commands.at(command_id).name.c_str());

    //             for (size_t length : commands.at(command_id).param_sizes) {
    //                 switch (length) {
    //                     case sizeof(u8):
    //                         Read<u8>();
    //                         break;
    //                     case sizeof(u16):
    //                         Read<u16>();
    //                         break;
    //                     case sizeof(u32): {
    //                         s32 value = Read<s32>();
    //                         switch (command_id) {
    //                             case 22:
    //                             case 26:
    //                             case 28:
    //                             case 29:
    //                                 function_offsets.push_back(cursor + value);
    //                                 break;
    //                             default:
    //                                 break;
    //                         }
    //                     }
    //                         break;
    //                     default:
    //                         printf("bad param length\n");
    //                         std::exit(1);
    //                 }
    //             }

    //                 // printf("\n");
                
    //             if (command_id == 0x0002 || command_id == 0x0016) {
    //                 break;
    //             }
    //         }
    //     }

    //     function_offsets = RemoveDuplicates(function_offsets);
    //     std::ranges::sort(function_offsets);
    // }

    // const size_t initial_size2 = function_offsets.size();
    // for (size_t i = 0; i < initial_size2; i++) {
    //     printf("Function #%lu:\n", i + 1);
    //     cursor = function_offsets.at(i);

    //     while (true) {
    //         u16 command_id = Read<u16>();

    //         printf("    %s", commands.at(command_id).name.c_str());

    //         for (size_t length : commands.at(command_id).param_sizes) {
    //             switch (length) {
    //                 case sizeof(u8):
    //                     printf(" 0x%02X", Read<u8>());
    //                     break;
    //                 case sizeof(u16):
    //                     printf(" 0x%04X", Read<u16>());
    //                     break;
    //                 case sizeof(u32): {
    //                     s32 value = Read<s32>();
    //                     switch (command_id) {
    //                         case 22:
    //                         case 26:
    //                         case 28:
    //                         case 29:
    //                             function_offsets.push_back(cursor + value);
    //                             break;
    //                     }
    //                     printf(" 0x%08X", value);
    //                 }
    //                     break;
    //                 default:
    //                     printf("bad param length\n");
    //                     std::exit(1);
    //             }
    //         }

    //             printf("\n");
            
    //         if (command_id == 0x0002 || command_id == 0x0016) {
    //             break;
    //         }
    //     }

    //     printf("\n");
    // }

    return 0;
}
