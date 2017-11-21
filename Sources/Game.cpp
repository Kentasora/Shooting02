#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A)
// TODO: 砲台を青い壁に沿って上下に動かす。(C)(実装:HW16A139 中村優太)
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B)(実装:HW16A139 中村優太)
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D)
// TODO: スコアのサイズを大きくする。(E)(実装:HW16A044 表 朋樹)
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F)
// TODO: PlayBGM()関数を使って、BGMを再生する。(HW16A104　杉本　雅弥)
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(HW16A104 杉本　雅弥)


Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
int     score;          //!< スコア

int     cannonCount = 0;          //砲台移動の判定


// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-80, -150);
    targetRect = Rect(80, -140, 40, 40);
    bulletPos.x = -999;
    score = 0;
    PlayBGM("bgm_maoudamashii_8bit07.mp3");
}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        PlaySound("se_maoudamashii_explosion03.mp3");
        bulletPos = cannonPos + Vector2(50, 10);
    }

    // 弾の移動
    if (bulletPos.x > -999) {
        bulletPos.x += 10 * Time::deltaTime;

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            PlaySound("se_maoudamashii_explosion06.mp3");
            score += 1;         // スコアの加算
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
        }
    }
    
    //雲の移動
    cloudPos.x += 1;
    if (cloudPos.x >= 480){
        cloudPos.x = -480;
    }

    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);

    // 雲の描画
    DrawImage("cloud1.png", cloudPos);

    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    DrawImage("cannon.png", cannonPos);
    
    //砲台の移動
    if (cannonPos.y >= -60 ) {
        cannonCount = 1;
    }
    if (cannonPos.y <= -150) {
        cannonCount = 0;
    }
    if (cannonCount == 0) {
        cannonPos.y += 1;
    }
    if (cannonCount == 1) {
        cannonPos.y -= 1;
    }

    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画
    SetFont("nicoca_v1.ttf", 100.0f);
    DrawText(FormatString("%02d", score), Vector2(-319, 149), Color::black);
    DrawText(FormatString("%02d", score), Vector2(-320, 150), Color::white);
}

